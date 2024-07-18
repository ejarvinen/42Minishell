/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_heredoc_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:11:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 11:19:47 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	write_hdoc_to_file(t_env *env, t_cmds *cmd)
{
	int		fd;
	
	if (g_sig > 0)
		return (1);
	fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: heredoc fail", 2);
		return (1);
	}
	heredoc_typer(env, cmd->heredoc, fd);
	close(fd);
	return (0);
}

int	add_heredoc_info(t_mini *shell, t_cmds *cmd, t_toks *token)
{
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(&shell->cmds);
		return (1);
	}
	heredoc(shell, cmd);
	shell->saved_stdin = -1;
	if (write_hdoc_to_file(shell->env, cmd) > 0)
	{
		ft_lstclear_pars(&shell->cmds);
		return (1);
	}
	return (0);
}

int	update_heredoc_info(t_mini *shell, t_cmds *cmd, t_toks *token)
{
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(&shell->cmds);
		return (1);
	}
	if (cmd->fd_infile > 1)
		close(cmd->fd_infile);
	heredoc(shell, cmd);
	if (write_hdoc_to_file(shell->env, cmd) > 0)
	{
		ft_lstclear_pars(&shell->cmds);
		return (1);
	}
	return (0);
}
