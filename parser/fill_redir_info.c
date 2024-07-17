/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:30 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/16 11:05:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (index);
	while (array[index])
	{
		index++;
	}
	return (index);
}

int	copy_filenames(char **to, char **from, char *new_file, int index)
{
	int	i;

	i = 0;
	if (from != NULL)
	{
		while (i < index)
		{
			to[i] = ft_strdup(from[i]);
			if (!to[i])
				return (1);
			i++;
		}
	}
	to[i] = ft_strdup(new_file);
	if (!to[i])
		return (1);
	to[i + 1] = NULL;
	return (0);
}

/*
if append is still uninitialized for a command, sets it's value to 0
*/
static t_toks	*append_checker(t_cmds *cmd, t_toks *token)
{
	if (cmd->append < 1)
		cmd->append = 0;
	token = token->next;
	return (token);
}

/*
loops through tokens and commands; adds filename, appends and heredoc delimeter
info to appropriate commands
*/
void	fill_redir_info(t_mini *shell, t_cmds **cmds, t_toks **tokens)
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
			if (syntax_checker(cmds, cmd, token, shell) > 0)
				return ;
		}
		else if (token->in_redir == 1 && struct_sum(token) == 1)
			token = add_infile_info(shell, cmd, token, 0);
		else if (token->out_redir == 1 && struct_sum(token) == 1)
			token = add_outfile_info(shell, cmd, token, 0);
		else if (token->append == 1 && struct_sum(token) == 1)
			token = add_outfile_info(shell, cmd, token, 1);
		else if (token->heredoc_delimiter == 1 && struct_sum(token) == 1)
			token = add_infile_info(shell, cmd, token, 1);
		else
			token = append_checker(cmd, token);
	}
}
