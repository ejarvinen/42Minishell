/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:12:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/22 11:02:42 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_mini *shell, t_cmds *cmd)
{
	if (cmd->fd_infile != 0)
		shell->saved_stdin = dup(STDIN_FILENO);
	if (cmd->fd_outfile[0] != 1)
		shell->saved_stdout = dup(STDOUT_FILENO);
	if (duplicate_fds(cmd) > 0)
	{
		restore_fds(shell);
		return ;
	}
	check_builtin(shell, cmd);
	if (cmd->fd_infile != 0)
		close(STDIN_FILENO);
	if (cmd->fd_outfile[0] != 1)
		close(STDOUT_FILENO);
	restore_fds(shell);
}

/*
runs a builtin command
*/
void	check_builtin(t_mini *shell, t_cmds *cmd)
{
	if (cmd->command[0] == NULL)
		return ;
	if (ft_strcmp(cmd->command[0], "export") == 0)
		export(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(shell, cmd);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		ft_env(shell, cmd);
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
}
