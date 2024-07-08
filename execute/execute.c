/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:34:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/08 08:37:15 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sets up pipes for command that's id is an even number
*/
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

/*
sets up pipes for command that's id is an odd number
*/
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

/*
if the command to be executed is not the first or the last command
in a pipeline, sets up pipes according to even and odd numbered ids
*/
static void	set_pipes(t_mini *shell, t_cmds *cmd, int *pipefds, char **env)
{
	if (cmd->id % 2 == 0)
	{
		if (even_id_cmds(cmd, pipefds) > 0)
			panic(shell, pipefds, env, 9);
	}
	else
	{
		if (odd_id_cmds(cmd, pipefds) > 0)
			panic(shell, pipefds, env, 9);
	}
}

/*
sets up pipes and redirections according to command type and runs
a builtin or execve accordingly
*/
void	execute(t_mini *shell, t_cmds *cmd, char **env, int *pipefds)
{
	if (cmd->id == 0)
		first_command(shell, cmd, pipefds, env);
	else if (cmd->id == cmd->commands - 1)
		last_command(shell, cmd, pipefds, env);
	else
		set_pipes(shell, cmd, pipefds, env);
	if (cmd->builtin == 1)
	{
		ft_freearray(env);
		check_builtin(shell, cmd);
	}
	else
	{
		if (execve(cmd->path, cmd->command, env) == -1)
			panic(shell, pipefds, env, 126);
	}
}
