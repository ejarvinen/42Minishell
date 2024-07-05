/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/05 09:35:04 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_builtin(t_mini *shell, t_cmds *cmd)
{
	int error;
	
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
	shell->EXIT_CODE = error;
}

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
	if (cmd->fd_outfile != 1)
	{
		if (dup2(cmd->fd_outfile, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close(cmd->fd_outfile);
	}
	return (0);
}

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
		if (duplicate_fds(cmd) > 0)
			return ;
		if (execve(cmd->path, cmd->command, env) == -1)
		{
			perror("minishell");
		}
	}
}

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
	run_multiple(shell, env, cmds);
}
