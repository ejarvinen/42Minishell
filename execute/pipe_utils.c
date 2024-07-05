/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/05 13:44:00 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// dup2 fail error code: 9
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

