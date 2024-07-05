/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:34:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/05 13:30:10 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	even_id_cmds(t_cmds *cmd, int *pipefds)
{
	close(pipefds[WRITE_END + 2]);
	if (cmd->fd_infile == 0)
		cmd->fd_infile = pipefds[READ_END + 2];
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
	{
		perror("minishell8");
		return (1);
	}
	close(cmd->fd_infile);
	close(pipefds[READ_END]);
	if (cmd->fd_outfile == 1)
		cmd->fd_outfile = pipefds[WRITE_END];
	if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
	{
		perror("minishell9");
		return (1);
	}
	close(cmd->fd_outfile);
	return (0);
}

static int	odd_id_cmds(t_cmds *cmd, int *pipefds)
{
	close(pipefds[WRITE_END]);
	if (cmd->fd_infile == 0)
		cmd->fd_infile = pipefds[READ_END];
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
	{
		perror("minishell10");
		return (1);
	}
	close(cmd->fd_infile);
	close(pipefds[READ_END + 2]);
	if (cmd->fd_outfile == 1)
		cmd->fd_outfile = pipefds[WRITE_END + 2];
	if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
	{
		perror("minishell11");
		return (1);
	}
	close(cmd->fd_outfile);
	return (0);
}

// dup2 fail error code: 9
static void	set_pipes(t_cmds *cmd, int *pipefds)
{
	if (cmd->id % 2 == 0)
	{
		if (even_id_cmds(cmd, pipefds) > 0)
			return ;
	}
	else
	{
		if (odd_id_cmds(cmd, pipefds) > 0)
			return ;
	}
}

// execve fail error code: 126
void	execute(t_mini *shell, t_cmds *cmd, char **env, int *pipefds)
{
	if (cmd->id == 0)
		first_command(cmd, pipefds);
	else if (cmd->id == cmd->commands - 1)
		last_command(cmd, pipefds);
	else
		set_pipes(cmd, pipefds);
	if (cmd->builtin == 1)
		check_builtin(shell, cmd);
	else
	{
		if (execve(cmd->path, cmd->command, env) == -1)
		{
			free_data(shell, NULL);
			exit(126);
		}
	}
}
