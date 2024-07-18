/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 08:43:21 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		{
			perror("minishell1");
			panic(shell, 9);
		}
		close(cmd->fd_infile);
	}
	if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
	{
		perror("minishell2");
		panic(shell, 9);
	}
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
	{
		perror("minishell3");
		panic(shell, 9);
	}
	close(cmd->fd_infile);
	if (cmd->fd_outfile[0] != 1)
	{
		if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		{
			perror("minishell4");
			panic(shell, 9);
		}
		close(cmd->fd_outfile[0]);
	}
}
