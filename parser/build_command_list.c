/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:38:13 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 16:05:39 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
returns the number of commands in a given list of tokens
*/
static int	count_cmds(t_toks **tokens)
{
	int		cmds;
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
	int		index;

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
returns a list of commands and their redirection info in a linked list
*/
t_cmds	*build_command_list(t_toks **tokens)
{
	int		commands;
	int		missing_cmd;
	t_cmds	*cmds;

	commands = count_cmds(tokens);
	missing_cmd = 0;
	if (!commands)
	{
		commands = 1;
		missing_cmd = 1;
	}
	cmds = NULL;
	create_list(&cmds, commands);
	if (!cmds)
		return (NULL);
	fill_cmd_info(&cmds, tokens, missing_cmd);
	if (!cmds)
		return (NULL);
	fill_redir_info(&cmds, tokens);
	if (!cmds)
		return (NULL);
	return (cmds);
}
