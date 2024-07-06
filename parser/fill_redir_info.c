/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:30 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 14:14:53 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
strdups infile name and saves it to cmd; adds corresponding append info
*/
static t_toks	*add_infile_info(t_cmds **cmds, t_cmds *cmd, t_toks *token)
{
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	cmd->infile_name = ft_strdup(token->content);
	if (!cmd->infile_name)
	{
		ft_lstclear_pars(cmds);
		return (NULL);
	}
	cmd->append = 0;
	return (token);
}

/*
strdups outfile name and saves it to cmd; adds corresponding append
info according to given flag
*/
static t_toks	*add_outfile_info(t_cmds **cmds, t_cmds *cmd,
	t_toks *token, int append_flag)
{
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	cmd->outfile_name = ft_strdup(token->content);
	if (!cmd->outfile_name)
	{
		ft_lstclear_pars(cmds);
		return (NULL);
	}
	cmd->append = append_flag;
	return (token);
}

/*
strdups a heredoc delimiter and saves it to cmd; adds corresponding append info
*/
static t_toks	*add_heredoc_info(t_cmds **cmds, t_cmds *cmd, t_toks *token)
{
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(cmds);
		return (NULL);
	}
	cmd->append = 0;
	return (token);
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
void	fill_redir_info(t_cmds **cmds, t_toks **tokens)
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
			if (syntax_checker(cmds, cmd, token) > 0)
				return ;
		}
		else if (token->in_redir == 1 && struct_sum(token) == 1)
			token = add_infile_info(cmds, cmd, token);
		else if (token->out_redir == 1 && struct_sum(token) == 1)
			token = add_outfile_info(cmds, cmd, token, 0);
		else if (token->append == 1 && struct_sum(token) == 1)
			token = add_outfile_info(cmds, cmd, token, 1);
		else if (token->heredoc_delimiter == 1 && struct_sum(token) == 1)
			token = add_heredoc_info(cmds, cmd, token);
		else
			token = append_checker(cmd, token);
	}
}
