/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multiple_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:24:20 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 13:36:38 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds the reading and writing ends of a pipe to array of pipe filedescriptors
*/
static void	add_pipefds(int *pipefds, int *index, int rd_end, int w_end)
{
	pipefds[*index] = rd_end;
	(*index)++;
	pipefds[*index] = w_end;
	(*index)++;
}

/*
mallocs an array of ints for a set of two pipes; if pipeline has only
two commands, the second pipeline is not opened, but marked as -1
*/
static int	*setup_pipes(t_cmds *cmds)
{
	int	*pipefds;
	int	fds[2];
	int	index;

	pipefds = (int *)malloc(sizeof(int) * 4);
	if (!pipefds)
	{
		perror("minishell");
		return (NULL);
	}
	index = 0;
	while (index < 4)
	{
		if (pipe(fds) < 0)
		{
			perror("minishell");
			free(pipefds);
			return (NULL);
		}
		if (index > 1 && cmds->commands == 2)
			add_pipefds(pipefds, &index, -1, -1);
		else
			add_pipefds(pipefds, &index, fds[READ_END], fds[WRITE_END]);
	}
	return (pipefds);
}

static int	execute_builtin(t_cmds *cmd)
{
	if (ft_strcmp(cmd->command[0], "cd") == 0 || (ft_strcmp(cmd->command[0], "export") == 0 && cmd->command[1] != NULL) || ft_strcmp(cmd->command[0], "unset") == 0 || ft_strcmp(cmd->command[0], "exit") == 0)
		return (1);
	return (0);
}

/*
forks a child process, executes it and closes pipes if running the last command
in the pipeline
*/
static void	child_process(t_mini *shell, t_cmds *cmd, char **env, int *pipefds)
{
	if (execute_builtin(cmd) > 0)
	{
		run_a_single_cmd(shell, env, cmd);
		return ;
	}
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		execute(shell, cmd, env, pipefds);
	}
	if (cmd->id == cmd->commands - 1)
	{
		close_pipes(pipefds);
	}
}

/*
waits each command in a pipeline to finish execution, saves it's exit code
and closes any open files and pipes if necessary
*/
static void	wait_for_children(t_cmds *cmds, int *pipefds)
{
	t_cmds	*cmd;
	int		status;

	cmd = cmds;
	while (cmd)
	{
		waitpid(cmd->c_pid, &status, 0);
		cmd->exit_status = status;
		if (cmd->heredoc != NULL)
			unlink(".temp");
		if (cmd->id == 0 && cmd->fd_infile > 0)
		{
			close(cmd->fd_infile);
			cmd->fd_infile = -1;
		}
		if (cmd->id == cmd->commands - 1 && cmd->fd_outfile[0] > 1)
		{
			close(cmd->fd_outfile[0]);
			cmd->fd_outfile[0] = -1;
		}
		if (cmd->id == cmd->commands - 1)
			close_pipes(pipefds);
		cmd = cmd->next;
	}
}

/*
runs a pipeline by setting up pipes, forks child processes for the
commands and then waits for the children to execute
*/
void	run_multiple(t_mini *shell, char **env, t_cmds *cmds)
{
	t_cmds	*cmd;
	int		*pipefds;

	pipefds = setup_pipes(cmds);
	if (!pipefds)
		return ;
	cmd = cmds;
	while (cmd)
	{
		child_process(shell, cmd, env, pipefds);
		cmd = cmd->next;
	}
	wait_for_children(cmds, pipefds);
	free(pipefds);
}
