/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:09:56 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 12:37:34 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sets redirections for a single command
*/
int	duplicate_fds(t_cmds *cmd)
{
	if (cmd->fd_infile != 0)
	{
		if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(cmd->fd_infile);
	}
	if (cmd->fd_outfile[0] != 1)
	{
		if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(cmd->fd_outfile[0]);
	}
	return (0);
}

/*
runs a single command in a child process
*/
static void	run_single(t_mini *shell, t_cmds *cmd)
{
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (ft_strcmp(cmd->command[0], "./minishell") == 0)
		set_signal(3);
	if (cmd->c_pid == 0)
	{
		if (duplicate_fds(cmd) > 0)
		{
			ft_freearray(shell->env_p);
			panic(shell, 9);
		}
		if (execve(cmd->path, cmd->command, shell->env_p) == -1)
		{
			ft_freearray(shell->env_p);
			panic(shell, 126);
		}
	}
}

void	restore_fds(t_mini *shell)
{
	if (shell->saved_stdin != -1)
	{
		dup2(shell->saved_stdin, STDIN_FILENO);
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
	if (shell->saved_stdout != -1)
	{
		dup2(shell->saved_stdout, STDOUT_FILENO);
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
}

void	run_a_single_cmd(t_mini *shell, t_cmds *cmd)
{
	int	status;

	if (cmd->builtin == 1)
	{
		run_builtin(shell, cmd);
	}
	else
	{
		shell->env_p = ltoa(&shell->env);
		if (!shell->env_p)
			return ;
		run_single(shell, cmd);
		waitpid(cmd->c_pid, &status, 0);
		cmd->exit_status = status;
		update_exitcode(shell, shell->cmds);
		ft_freearray(shell->env_p);
	}
}

/*
fetches environment variables and executes either a single command
or a pipeline
*/
void	run_commands(t_mini *shell)
{
	t_cmds	*cmds;

	cmds = shell->cmds;
	if (cmds->commands == 1)
	{
		if (safe_to_run(cmds) < 1 || cmds->command == NULL
			|| cmds->fd_infile == -1)
		{
			if (cmds->heredoc != NULL)
				unlink(".temp");
			return ;
		}
		run_a_single_cmd(shell, cmds);
		if (cmds->heredoc != NULL)
			unlink(".temp");
		return ;
	}
	run_multiple(shell, cmds);
}
