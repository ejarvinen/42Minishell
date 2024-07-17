/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/17 09:29:24 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
closes any open pipes in pipefds
*/
void	close_pipes(int *pipefds)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		if (pipefds[index] != -1)
			close(pipefds[index]);
		index++;
	}
}

/*
sets up file descriptors and redirections for the first command in a pipeline
*/
void	first_command(t_mini *shell, t_cmds *cmd)
{
	close(shell->pipefds[READ_END]);
	if (cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
		{
			perror("minishell");
			panic(shell, 9);
		}
		close(cmd->fd_infile);
	}
	if (cmd->fd_outfile[0] == 1)
		cmd->fd_outfile[0] = shell->pipefds[WRITE_END];
	else
		close(shell->pipefds[WRITE_END]);
	if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
	{
		perror("minishell");
		panic(shell, 9);
	}
	close(cmd->fd_outfile[0]);
	if (cmd->commands > 2)
	{
		close(shell->pipefds[READ_END + 2]);
		close(shell->pipefds[WRITE_END + 2]);
	}
}

/*
sets up filedescriptors and redirections for the last command
in a pipeline when command id is an even number
*/
static int	even_commands(t_cmds *cmd, int *pipefds)
{
	close(pipefds[WRITE_END]);
	if (cmd->fd_infile == 0)
		cmd->fd_infile = pipefds[READ_END];
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (1);
	}
	close(cmd->fd_infile);
	if (cmd->fd_outfile[0] != 1)
	{
		if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(cmd->fd_outfile[0]);
	}
	if (cmd->commands > 2)
	{
		close(pipefds[READ_END + 2]);
		close(pipefds[WRITE_END + 2]);
	}
	return (0);
}

/*
sets up filedescriptors and redirections for the last command
in a pipeline when command id is an odd number
*/
static int	odd_commands(t_cmds *cmd, int *pipefds)
{
	close(pipefds[WRITE_END + 2]);
	if (cmd->fd_infile == 0)
		cmd->fd_infile = pipefds[READ_END + 2];
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (1);
	}
	close(cmd->fd_infile);
	if (cmd->fd_outfile[0] != 1)
	{
		if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(cmd->fd_outfile[0]);
	}
	close(pipefds[READ_END]);
	close(pipefds[WRITE_END]);
	return (0);
}

/*
sets up filedescritors and redirections for the last command in a pipeline
*/
void	last_command(t_mini *shell, t_cmds *cmd)
{
	if (cmd->commands % 2 == 0)
	{
		if (even_commands(cmd, shell->pipefds) > 0)
			panic(shell, 9);
	}
	else
	{
		if (odd_commands(cmd, shell->pipefds) > 0)
			panic(shell, 9);
	}
}
