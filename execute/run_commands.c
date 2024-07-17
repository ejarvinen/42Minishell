/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/17 08:13:11 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sets redirections for a single command
*/
static int	duplicate_fds(t_cmds *cmd)
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
static void	run_single(t_mini *shell, t_cmds *cmd, char **env)
{
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		if (duplicate_fds(cmd) > 0)
			panic(shell, NULL, env, 9);
		if (execve(cmd->path, cmd->command, env) == -1)
		{
			perror("minishell");
			panic(shell, NULL, env, 126);
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

void	run_a_single_cmd(t_mini *shell, char **env, t_cmds *cmd)
{
	int		status;

	if (cmd->builtin == 1)
	{
		shell->saved_stdin = dup(STDIN_FILENO);
		shell->saved_stdout = dup(STDOUT_FILENO);
		ft_freearray(env);
		if (duplicate_fds(cmd) > 0)
			return ;
		check_builtin(shell, cmd);
		if (cmd->fd_infile != 0)
			close(STDIN_FILENO);
		if (cmd->fd_outfile[0] != 1)
			close(STDOUT_FILENO);
		restore_fds(shell);
	}
	else
	{
		run_single(shell, cmd, env);
		waitpid(cmd->c_pid, &status, 0);
		cmd->exit_status = status;
	}
}

/*
fetches environment variables and executes either a single command
or a pipeline
*/
void	run_commands(t_mini *shell)
{
	t_cmds	*cmds;
	char	**env;

	cmds = shell->cmds;
	env = ltoa(shell->env);
	if (!env)
		return ;
	if (cmds->commands == 1)
	{
		if (safe_to_run(cmds) < 1)
		{
			ft_freearray(env);
			if (cmds->heredoc != NULL)
				unlink(".temp");
			return ;
		}
		run_a_single_cmd(shell, env, cmds);
		if (cmds->builtin != 1)
			ft_freearray(env);
		if (cmds->heredoc != NULL)
			unlink(".temp");
		return ;
	}
	run_multiple(shell, env, cmds);
	ft_freearray(env);
	update_exitcode(shell, shell->cmds);
}
