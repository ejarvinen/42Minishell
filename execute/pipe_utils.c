/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 11:45:29 by emansoor         ###   ########.fr       */
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
void	first_command(t_mini *shell, t_cmds *cmd, int *pipefds)
{
	close(pipefds[READ_END]);
	if (cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
		{
			perror("minishell2");
			panic(shell, pipefds, 9);
		}
		close(cmd->fd_infile);
	}
	if (cmd->fd_outfile == 1)
		cmd->fd_outfile = pipefds[WRITE_END];
	else
		close(pipefds[WRITE_END]);
	if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
	{
		perror("minishell3");
		panic(shell, pipefds, 9);
	}
	close(cmd->fd_outfile);
	if (cmd->commands > 2)
	{
		close(pipefds[READ_END + 2]);
		close(pipefds[WRITE_END + 2]);
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
		perror("minishell4");
		return (1);
	}
	close(cmd->fd_infile);
	if (cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
		{
			perror("minishell5");
			return (1);
		}
		close(cmd->fd_outfile);
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
		perror("minishell6");
		return (1);
	}
	close(cmd->fd_infile);
	if (cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
		{
			perror("minishell7");
			return (1);
		}
		close(cmd->fd_outfile);
	}
	close(pipefds[READ_END]);
	close(pipefds[WRITE_END]);
	return (0);
}

/*
sets up filedescritors and redirections for the last command in a pipeline
*/
void	last_command(t_mini *shell, t_cmds *cmd, int *pipefds)
{
	if (cmd->commands % 2 == 0)
	{
		if (even_commands(cmd, pipefds) > 0)
			panic(shell, pipefds, 9);
	}
	else
	{
		if (odd_commands(cmd, pipefds) > 0)
			panic(shell, pipefds, 9);
	}
}
