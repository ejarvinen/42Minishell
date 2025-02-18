/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:08:48 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 15:16:06 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_heredoc_specs(t_mini *shell, t_cmds *cmd, t_toks *token,
int first)
{
	char	*freeable;

	freeable = NULL;
	if (first > 0)
		freeable = cmd->infile_name;
	cmd->infile_name = ft_strdup(".temp");
	if (!cmd->infile_name)
	{
		ft_lstclear_pars(&shell->cmds);
		return (1);
	}
	if (first > 0)
	{
		free(freeable);
		if (update_heredoc_info(shell, cmd, token) > 0)
			return (1);
	}
	else
	{
		if (add_heredoc_info(shell, cmd, token) > 0)
			return (1);
	}
	return (0);
}

static int	first_infile(t_mini *shell, t_cmds *cmd, t_toks *token,
int heredoc_flag)
{
	if (heredoc_flag)
	{
		if (init_heredoc_specs(shell, cmd, token, 0) > 0)
			return (1);
	}
	else
	{
		cmd->infile_name = ft_strdup(token->content);
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(&shell->cmds);
			return (1);
		}
		cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
		if (cmd->fd_infile < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->infile_name);
			exit_code(shell, 1, 0);
		}
	}
	return (0);
}

static void	update_fd(t_mini *shell, t_cmds *cmd)
{
	int		prev_fd;

	prev_fd = cmd->fd_infile;
	if (prev_fd > 1)
		close(prev_fd);
	cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
	if (cmd->fd_infile < 0 && prev_fd != -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->infile_name);
		exit_code(shell, 1, 0);
	}
}

static int	update_existing_infile(t_mini *shell, t_cmds *cmd, t_toks *token,
int heredoc_flag)
{
	char	*freeable;

	if (heredoc_flag)
	{
		if (init_heredoc_specs(shell, cmd, token, 1) > 0)
			return (1);
	}
	else
	{
		freeable = cmd->infile_name;
		cmd->infile_name = ft_strdup(token->content);
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(&shell->cmds);
			return (1);
		}
		free(freeable);
		update_fd(shell, cmd);
	}
	return (0);
}

/*
strdups infile name and saves it to cmd; adds corresponding append info
*/
t_toks	*add_infile_info(t_mini *shell, t_cmds *cmd, t_toks *token,
int heredoc_flag)
{
	token = token->next;
	if (syntax_check(token, &shell->cmds, shell) > 0)
		return (NULL);
	if (cmd->infile_name == NULL)
	{
		if (first_infile(shell, cmd, token, heredoc_flag) > 0)
			return (NULL);
	}
	else
	{
		if (update_existing_infile(shell, cmd, token, heredoc_flag) > 0)
			return (NULL);
	}
	return (token);
}
