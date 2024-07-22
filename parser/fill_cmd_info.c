/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:00:21 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/22 12:38:52 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
counts arguments in the given pipeline specified by cmd_id
*/
static int	args_count(t_toks **tokens, int cmd_id)
{
	t_toks	*token;
	int		args;

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
	int		arg_count;

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

/*
mallocs 2D array for the command and it's arguments and strdups
command to index 0 in the 2D array
*/
static int	get_command_array(t_cmds *cmd, t_toks *token, int arrlen)
{
	cmd->command = (char **)malloc(sizeof(char *) * (arrlen + 2));
	if (!cmd->command)
		return (1);
	cmd->command[0] = ft_strdup(token->content);
	if (!cmd->command[0])
	{
		ft_freearray(cmd->command);
		return (1);
	}
	return (0);
}

/*
builds a 2D array consisting of a command and any possible command arguments
*/
static void	add_cmd_info(t_cmds *cmd, t_toks **tokens,
	t_toks *token, int arrlen)
{
	int	index;

	if (get_command_array(cmd, token, arrlen) > 0)
		return ;
	index = 1;
	if (arrlen > 0)
	{
		while (index <= arrlen)
		{
			cmd->command[index] = ft_strdup(get_arg(tokens, token, index));
			if (!cmd->command[index])
			{
				ft_freearray(cmd->command);
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
void	fill_cmd_info(t_cmds **cmds, t_toks **tokens)
{
	t_toks	*token;
	t_cmds	*cmd;
	int		array_len;

	cmd = *cmds;
	token = *tokens;
	while (token && cmd)
	{
		if (token->pipe == 1 && check_for_previous_cmds(tokens, token->id) == 0)
			cmd = cmd->next;
		else if (token->command == 1 && struct_sum(token) == 1)
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
	/* while (token)
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
	} */
}
