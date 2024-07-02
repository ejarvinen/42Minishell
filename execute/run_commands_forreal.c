/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands_forreal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:20:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 11:51:57 by emansoor         ###   ########.fr       */
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
		if (execve(cmd->path, cmd->command, env) == -1)
		{
			perror("minishell");
		}
	}
}

/*
creates a pipe and returns a pointer to the pipe end filedescriptors
*/
/*static int	*pipesetup(int pipes)
{
	int	*pipefds;
	int	fd[2];

	pipefds = (int *)malloc(sizeof(int) * pipes);
	if (!pipefds)
	{
		perror("minishell");
		return (NULL);
	}
	if (pipe(fds) < 0)
	{
		perror("pipex");
		free(pipefds);
		return (NULL);
	}
	pipefds[READ_END] = fds[READ_END];
	pipefds[WRITE_END] = fds[WRITE_END];
	return (pipefds);
}

static void	fancy_pipex(t_mini *shell, char **env, t_cmds *cmds)
{
	t_cmds	*cmd;
	int		*pipefds;
	int		status;

	pipefds = pipesetup(cmds->commands);
	if (!pipefds)
		return ;
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
