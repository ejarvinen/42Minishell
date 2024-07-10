/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 18:23:59 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_heredoc_info(t_cmds **cmds, t_cmds *cmd, t_toks *token)
{
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(cmds);
		return (1);
	}
	cmd->fd_infile = 0;
	return (0);
}

int	update_heredoc_info(t_cmds **cmds, t_cmds *cmd, t_toks *token)
{
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(cmds);
		return (1);
	}
	if (cmd->fd_infile > 1)
		close(cmd->fd_infile);
	cmd->fd_infile = 0;
	return (0);
}
