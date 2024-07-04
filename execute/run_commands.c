/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/04 10:40:36 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_fds(t_mini *shell, int fd_type)
{
	if (fd_type == 0 && shell->saved_stdin != -1)
	{
		if (dup2(shell->saved_stdin, STDIN_FILENO) < 0)
		{
			perror("minishell");
			//free_data(shell, "failed to restore STDIN");
		}
		close(shell->saved_stdin);
	}
	else if (fd_type == 1 && shell->saved_stdin != -1)
	{
		if (dup2(shell->saved_stdout, STDOUT_FILENO) < 0)
		{
			perror("minishell");
			//free_data(shell, "failed to restore STDOUT");
		}
		close(shell->saved_stdout);
	}
}

void	check_builtin(t_mini *shell, t_cmds *cmd)
{
	int error;
	
	if (cmd->command[0] == NULL)
		return ;
	if (ft_strcmp(cmd->command[0], "export") == 0)
		export(&shell->env, cmd->command, cmd->fd_outfile);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(&shell->env, cmd->command);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		error = ft_env(shell);
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(shell, cmd->command);
	else if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		now_exit(shell, cmd->command);
	shell->EXIT_CODE = error;
}
