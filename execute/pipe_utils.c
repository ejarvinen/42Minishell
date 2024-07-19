/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/19 10:07:03 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dup_fail(t_mini *shell)
{
	perror("minishell");
	panic(shell, 9);
}

/*
sets up file descriptors and redirections for the first command in a pipeline
*/
void	first_command(t_mini *shell, t_cmds *cmd)
{
	t_cmds	*next;

	next = cmd->next;
	while (next)
	{
		if (next->fd_infile != 0)
			close(next->fd_infile);
		if (next->fd_outfile[0] != 1)
			close(next->fd_outfile[0]);
		next = next->next;
	}
	if (cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
			dup_fail(shell);
		close(cmd->fd_infile);
	}
	if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		dup_fail(shell);
	close(cmd->fd_outfile[0]);
}

/*
sets up filedescritors and redirections for the last command in a pipeline
*/
void	last_command(t_mini *shell, t_cmds *cmd)
{
	t_cmds	*prev;

	prev = shell->cmds;
	while (prev->id < prev->commands - 1)
	{
		if (prev->fd_infile != 0)
			close(prev->fd_infile);
		if (prev->fd_outfile[0] != 1)
			close(prev->fd_outfile[0]);
		prev = prev->next;
	}
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
		dup_fail(shell);
	close(cmd->fd_infile);
	if (cmd->fd_outfile[0] != 1)
	{
		if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
			dup_fail(shell);
		close(cmd->fd_outfile[0]);
	}
}

static void	close_extra_pipes(t_mini *shell, t_cmds *cmd)
{
	t_cmds	*next;
	t_cmds	*prev;

	prev = shell->cmds;
	while (prev->id != cmd->id)
	{
		if (prev->fd_infile != 0)
			close(prev->fd_infile);
		if (prev->fd_outfile[0] != 1)
			close(prev->fd_outfile[0]);
		prev = prev->next;
	}
	next = cmd->next;
	while (next)
	{
		if (next->fd_infile != 0)
			close(next->fd_infile);
		if (next->fd_outfile[0] != 1)
			close(next->fd_outfile[0]);
		next = next->next;
	}
}

/*
if the command to be executed is not the first or the last command
in a pipeline, sets up pipes according to even and odd numbered ids
*/
void	set_pipes(t_mini *shell, t_cmds *cmd)
{
	close_extra_pipes(shell, cmd);
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
		dup_fail(shell);
	close(cmd->fd_infile);
	if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		dup_fail(shell);
	close(cmd->fd_outfile[0]);
}
