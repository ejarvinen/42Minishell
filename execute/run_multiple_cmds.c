/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_multiple_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:13:53 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 09:46:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_ids(t_cmds *cmd)
{
	t_cmds	*next;
	int		new_id;

	if (cmd->fd_infile != 0)
		close(cmd->fd_infile);
	if (cmd->fd_outfile[0] != 1)
		close(cmd->fd_outfile[0]);
	next = cmd->next;
	new_id = 0;
	while (next)
	{
		next->id = new_id;
		new_id++;
		next = next->next;
	}
}

static int	setup_pipes(t_cmds *cmd)
{
	int		fds[2];
	t_cmds	*next;

	next = cmd->next;
	if (cmd->command == NULL && next->command == NULL)
		return (1);
	if (pipe(fds) < 0)
	{
		perror("minishell");
		return (1);
	}
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
	t_cmds	*next;

	next = cmd->next;
	if (next && next->valid == -1)
		return ;
	if (cmd->id < cmd->commands - 1 && setup_pipes(cmd) > 0)
		return ;
	if (cmd->command != NULL && cmd->fd_infile != -1)
	{
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
	if (cmd->command == NULL || cmd->fd_infile < 0)
		update_ids(cmd);
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
		if (safe_to_run(cmd) > 0)
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
		else if (cmd->heredoc != NULL)
			unlink(".temp");
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
	shell->env_p = ltoa(&shell->env);
	if (!shell->env_p)
		return ;
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
	ft_freearray(shell->env_p);
}
