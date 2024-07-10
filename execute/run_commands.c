/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 08:12:48 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
runs a builtin command
*/
void	check_builtin(t_mini *shell, t_cmds *cmd)
{
	int	error;

	if (cmd->command[0] == NULL)
		return ;
	if (ft_strcmp(cmd->command[0], "export") == 0)
		export(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		error = ft_env(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		pwd(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		now_exit(shell, cmd->command);
	else if (ft_strcmp(cmd->command[0], "$?") == 0)
		write_exit(shell, cmd);
	shell->EXIT_CODE = error;
}

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

static void	run_a_single_cmd(t_mini *shell, char **env, t_cmds *cmds)
{
	int		status;

	if (cmds->builtin == 1)
	{
		ft_freearray(env);
		check_builtin(shell, cmds);
	}
	else
	{
		run_single(shell, cmds, env);
		waitpid(cmds->c_pid, &status, 0);
		cmds->exit_status = status;
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
		run_a_single_cmd(shell, env, cmds);
		if (cmds->builtin != 1)
			ft_freearray(env);
		if (cmds->heredoc != NULL)
			unlink(".temp");
		return ;
	}
	run_multiple(shell, env, cmds);
	ft_freearray(env);
}
