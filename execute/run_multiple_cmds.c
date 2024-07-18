/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multiple_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:24:20 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 15:56:51 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execute_builtin(t_cmds *cmd)
{
	if (ft_strcmp(cmd->command[0], "cd") == 0
		|| (ft_strcmp(cmd->command[0], "export") == 0
			&& cmd->command[1] != NULL)
		|| ft_strcmp(cmd->command[0], "unset") == 0
		|| ft_strcmp(cmd->command[0], "exit") == 0)
		return (1);
	return (0);
}

static int	setup_pipes(t_cmds *cmd)
{
	int		fds[2];
	t_cmds	*next;

	if (cmd->id < cmd->commands - 1)
	{
		if (pipe(fds) < 0)
		{
			perror("minishell");
			return (1);
		}
	}
	next = cmd->next;
	if (cmd->id < cmd->commands - 1 && cmd->fd_outfile[0] == 1)
		cmd->fd_outfile[0] = fds[WRITE_END];
	else if (cmd->id < cmd->commands - 1 && cmd->fd_outfile[0] != 1)
		close(fds[WRITE_END]);
	if (next && next->fd_infile == 0)
		next->fd_infile = fds[READ_END];
	else if (next && next->fd_infile != 0)
		close(fds[READ_END]);
	return (0);
}

/*
forks a child process, executes it and closes pipes if running the last command
in the pipeline
*/
static void	child_process(t_mini *shell, t_cmds *cmd)
{
	if (execute_builtin(cmd) > 0)
	{
		run_a_single_cmd(shell, cmd);
		return ;
	}
	if (setup_pipes(cmd) > 0)
		return ;
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		execute(shell, cmd);
	}
}

/*
waits each command in a pipeline to finish execution, saves it's exit code
and closes any open files and pipes if necessary
*/
static void	wait_for_children(t_cmds *cmds)
{
	t_cmds	*cmd;
	int		status;

	cmd = cmds;
	while (cmd)
	{
		if (safe_to_run(cmd) > 0 && execute_builtin(cmd) < 1)
		{
			waitpid(cmd->c_pid, &status, 0);
			cmd->exit_status = status;
			if (cmd->heredoc != NULL)
				unlink(".temp");
			if (cmd->fd_infile != 0)
				close(cmd->fd_infile);
			if (cmd->fd_outfile[0] != 1)
				close(cmd->fd_outfile[0]);
		}
		cmd = cmd->next;
	}
}

/*
runs a pipeline by setting up pipes, forks child processes for the
commands and then waits for the children to execute
*/
void	run_multiple(t_mini *shell, t_cmds *cmds)
{
	t_cmds	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (safe_to_run(cmd) > 0)
		{
			child_process(shell, cmd);
		}
		cmd = cmd->next;
	}
	wait_for_children(cmds);
	update_exitcode(shell, shell->cmds);
}
