/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_forreal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 12:53:14 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_single(/*t_mini *shell, */t_cmds *cmd, char **env)
{
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		if (cmd->fd_infile != 0)
		{
			if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
			{
				perror("minishell");
				return ;
			}
			close(cmd->fd_infile);
		}
		if (cmd->fd_outfile != 1)
		{
			if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
			{
				perror("minishell");
				return ;
			}
			close(cmd->fd_outfile);
		}
		if (execve(cmd->path, cmd->command, env) == -1)
		{
			perror("minishell");
		}
	}
}
/*

static int	*pipesetup(int pipes)
{
	int	*pipefds;
	int	fds[2];
	int	index;

	pipefds = (int *)malloc(sizeof(int) * 2 * pipes);
	if (!pipefds)
	{
		perror("minishell");
		return (NULL);
	}
	index = 0;
	while (pipes > 0)
	{
		if (pipe(fds) < 0)
		{
			perror("minishell");
			free(pipefds);
			return (NULL);
		}
		pipefds[index] = fds[READ_END];
		index++;
		pipefds[index] = fds[WRITE_END];
		index++;
		pipes--;
	}
	return (pipefds);
}

static void	execute(t_mini *shell, t_cmds *cmd, int *pipefds, char **env)
{
	
	if (execve(cmd->path, cmd->command, env) == -1)
	{
		perror("minishell");
	}
}

static void	close_all_pipes(int *pipefds, int pipes)
{
	int	index;

	index = 0;
	while (index < pipes)
	{
		close(pipefds[index]);
		index++;
	}
}

static void	child_process(t_mini *shell, t_cmds *cmd, int *pipefds, char **env)
{
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		execute(shell, cmd, pipefds, env);
	}
	if (cmd->id == cmd->commands - 1)
	{
		close_all_pipes(pipefds, 2 * (cmd->commands - 1));
	}
}

static void	fancy_pipex(t_mini *shell, char **env, t_cmds *cmds)
{
	t_cmds	*cmd;
	int		*pipefds;
	int		status;

	pipefds = pipesetup(cmds->commands - 1);
	if (!pipefds)
		return ;
	cmd = cmds;
	while (cmd)
	{
		child_process(shell, cmd, pipefds, env);
		cmd = cmd->next;
	}
}*/

void	run_commands(t_mini *shell)
{
	t_cmds	*cmds;
	int		status;
	char	**env;
	
	cmds = shell->cmds;
	env = ltoa(shell->env);
	if (!env)
		return ;
	if (cmds->commands == 1)
	{
		if (cmds->builtin == 1)
			check_builtin(shell, cmds);
		else
		{
			run_single(/*shell, */cmds, env);
			waitpid(cmds->c_pid, &status, 0);
			cmds->exit_status = status;
		}
		return ;
	}
	//fancy_pipex(shell, env, cmds);
}
