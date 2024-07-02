/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:38:13 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 09:05:39 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
returns the number of commands in a given list of tokens
*/
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

/*
creates a linked list of size lst_size and adds indexes to all nodes
*/
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
			ft_lstclear_pars(cmds);
			return ;
		}
		ft_lstadd_back_pars(cmds, new_node);
		index++;
		lst_size--;
	}
}

/*
counts arguments in the given pipeline specified by cmd_id
*/
static int	args_count(t_toks **tokens, int cmd_id)
{
	t_toks	*token;
	int	args;

	token = *tokens;
	args = 0;
	if (ft_lstsize_toks(token) == 1)
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

/*
returns command argument specified by given index
*/
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
	
	cmd->command = (char **)malloc(sizeof(char *) * (arrlen + 2));
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
			if (!cmd->command[index])
			{
				free_array(cmd->command);
				return ;
			}
			index++;
		}
	}
	cmd->command[index] = NULL;
}

/*
creates a 2D char array containing command and it's possible arguments
in the current pipeline and adds it to the command list
*/
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
				ft_lstclear_pars(cmds);
				return ;
			}
			cmd = cmd->next;
		}
		token = token->next;
	}
}

/*
returns syntax error message for delimeters missing file info / heredoc
*/
static int	syntax_check(t_toks *token, t_cmds **cmds)
{
	if (token == NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		ft_lstclear_pars(cmds);
		return (1);
	}
	return (0);
}

static void	fill_redir_info(t_cmds **cmds, t_toks **tokens)
{
	t_toks	*token;
	t_cmds	*cmd;

	token = *tokens;
	cmd = *cmds;
	while (token && cmd)
	{
		if (token->id > 0 && token->pipe == 1 && struct_sum(token) == 1)
		{
			cmd = cmd->next;
			token = token->next;
			if (token == NULL)
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				ft_lstclear_pars(cmds);
				return ;
			}
			else if (cmd == NULL && token != NULL)
			{
				syntax_check(NULL, cmds);
				return ;
			}
			else if (cmd == NULL)
				return ;
			cmd->append = 0;
		}
		else if (token->in_redir == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			if (syntax_check(token, cmds) > 0)
				return ;
			cmd->infile_name = ft_strdup(token->content);
			if (!cmd->infile_name)
			{
				ft_lstclear_pars(cmds);
				return ;
			}
			cmd->append = 0;
		}
		else if (token->out_redir == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			if (syntax_check(token, cmds) > 0)
				return ;
			cmd->outfile_name = ft_strdup(token->content);
			if (!cmd->outfile_name)
			{
				ft_lstclear_pars(cmds);
				return ;
			}
			cmd->append = 0;
		}
		else if (token->append == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			if (syntax_check(token, cmds) > 0)
				return ;
			cmd->outfile_name = ft_strdup(token->content);
			if (!cmd->outfile_name)
			{
				ft_lstclear_pars(cmds);
				return ;
			}
			cmd->append = 1;
		}
		else if (token->heredoc_delimiter == 1 && struct_sum(token) == 1)
		{
			token = token->next;
			if (syntax_check(token, cmds) > 0)
				return ;
			cmd->heredoc = ft_strdup(token->content);
			if (!cmd->heredoc)
			{
				ft_lstclear_pars(cmds);
				return ;
			}
			cmd->append = 0;
		}
		else
		{
			if (cmd->append < 1)
				cmd->append = 0;
			token = token->next;
		}
	}
}

/*
returns a list of commands and their redirection info in a linked list
*/
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
	return (cmds);
}


	// if infile/outfile name is missing, mark fds to -2 for error