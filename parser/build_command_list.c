/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:38:13 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/07 12:08:11 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_cmds(t_toks **tokens)
{
	int	cmds;
	t_toks	*token;

	cmds = 0;
	token = *tokens;
	while (token)
	{
		if (token->command > 0)
			cmds++;
		token = token->next;
	}
	return (cmds);
}

static void	create_list(t_cmds **cmds, int lst_size)
{
	t_cmds	*new_node;
	int	index;

	index = 0;
	while (lst_size > 0)
	{
		new_node = ft_lstnew_pars(index);
		if (!new_node)
		{
			ft_lstclear_pars(cmds, free);
			return ;
		}
		ft_lstadd_back_pars(cmds, new_node);
		index++;
		lst_size--;
	}
}

static int	args_count(t_toks **tokens, int cmd_id)
{
	t_toks	*token;
	int	args;

	token = *tokens;
	args = 0;
	if (cmd_id == ft_lstsize_toks(token) - 1)
		return (args);
	while (token->id != cmd_id)
		token = token->next;
	token = token->next;
	while (token && token->command != 1 && token->pipe != 1)
	{
		if (token->argument == 1 && struct_sum(token) == 1)
			args++;
		token = token->next;
	}
	return (args);
}

static char	*get_arg(t_toks **tokens, t_toks *token, int index)
{
	t_toks	*tok;
	int	arg_count;

	arg_count = 0;
	tok = *tokens;
	while (tok->id != token->id)
		tok = tok->next;
	tok = tok->next;
	while (tok && tok->command != 1 && tok->pipe != 1)
	{
		if (tok->argument == 1 && struct_sum(tok) == 1)
		{
			if (arg_count == index - 1)
				return (tok->content);
			else
				arg_count++;
		}
		tok = tok->next;
	}
	return (NULL);
}

static void	add_cmd_info(t_cmds *cmd, t_toks **tokens, t_toks *token, int arrlen)
{
	int	index;
	
	cmd->command = (char **)malloc(sizeof(char *) * 2 + sizeof(char *) * arrlen);
	if (!cmd->command)
		return ;
	cmd->command[0] = ft_strdup(token->content);
	if (!cmd->command[0])
	{
		free_array(cmd->command);
		return ;
	}
	index = 1;
	if (arrlen > 0)
	{
		while (index <= arrlen)
		{
			cmd->command[index] = ft_strdup(get_arg(tokens, token, index));
			if (!cmd->command[0])
			{
				free_array(cmd->command);
				return ;
			}
			index++;
		}
	}
	cmd->command[index] = NULL;
}

static void	fill_cmd_info(t_cmds **cmds, t_toks **tokens)
{
	t_toks	*token;
	t_cmds	*cmd;
	int	array_len;

	token = *tokens;
	cmd = *cmds;
	while (token)
	{
		if (token->command == 1 && struct_sum(token) == 1)
		{
			array_len = args_count(tokens, token->id);
			add_cmd_info(cmd, tokens, token, array_len);
			if (cmd->command == NULL)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
			cmd = cmd->next;
		}
		token = token->next;
	}
}

static void	fill_redir_info(t_cmds **cmds, t_toks **tokens)
{
	t_toks	*token;
	t_cmds	*cmd;
	int	cmd_index;

	token = *tokens;
	cmd = *cmds;
	cmd_index = 0;
	while (token && cmd)
	{
		if (token->id > 0 && token->pipe == 1 && struct_sum(token) == 1)
		{
			cmd = cmd->next;
			token = token->next;
			if (token == NULL || cmd == NULL)
				return ;
		}
		if (token->in_redir == 1 && struct_sum(token) == 1)
		{
			token = token->next; // needs a check if it's null?
			cmd->infile_name = ft_strdup(token->content);
			if (!cmd->infile_name)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		if (token->out_redir == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			cmd->outfile_name = ft_strdup(token->content);
			if (!cmd->outfile_name)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		if (token->append == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			cmd->outfile_name = ft_strdup(token->content);
			if (!cmd->outfile_name)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		if (token->heredoc_delimiter == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			cmd->heredoc = ft_strdup(token->content);
			if (!cmd->heredoc)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		token = token->next;
	}
}

static void	fill_missing_chartypes(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->infile_name == NULL)
		{
			cmd->infile_name = ft_strdup("0");
			if (!cmd->infile_name)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		if (cmd->outfile_name == NULL)
		{
			cmd->outfile_name = ft_strdup("0");
			if (!cmd->outfile_name)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		if (cmd->heredoc == NULL)
		{
			cmd->heredoc = ft_strdup("0");
			if (!cmd->heredoc)
			{
				ft_lstclear_pars(cmds, free);
				return ;
			}
		}
		cmd = cmd->next;
	}
}

t_cmds	*build_command_list(t_toks **tokens)
{
	int	commands;
	t_cmds	*cmds;
	
	commands = count_cmds(tokens);
	if (!commands)
		return (NULL);
	cmds = NULL;
	create_list(&cmds, commands);
	if (!cmds)
		return (NULL);
	fill_cmd_info(&cmds, tokens);
	if (!cmds)
		return (NULL);
	fill_redir_info(&cmds, tokens);
	if (!cmds)
		return (NULL);
	fill_missing_chartypes(&cmds);
	if (!cmds)
		return (NULL);
	return (cmds);
}


	// if infile/outfile name is missing, mark fds to -2 for error