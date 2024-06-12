/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:59:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/12 15:12:34 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
checks for an empty file and saves its fd into first command, opens outfile
and saves its fd into last command in cmds
*/
static void	open_outfiles(t_cmds *cmd)
{
	if (cmd->outfile_name == NULL)
		cmd->fd_outfile = 1;
	else
	{
		cmd->fd_outfile = open(cmd->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (cmd->fd_outfile < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->outfile_name);
		}
	}
}

/*
checks if infile exists
*/
static void	open_infile(t_cmds *cmd)
{
	if (cmd->infile_name == NULL)
		cmd->fd_infile = 0;
	else
	{
		cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
		if (cmd->fd_infile < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->infile_name);
		}
	}
}

void	close_files(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->fd_infile > 1)
			close(cmd->fd_infile);
		if (cmd->fd_outfile > 1)
			close(cmd->fd_outfile);
		cmd = cmd->next;
	}
}

void	open_files(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		open_infile(cmd);
		open_outfiles(cmd);
		cmd = cmd->next;
	}
}
