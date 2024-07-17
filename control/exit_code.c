/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:51:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/17 11:20:35 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_mini *shell, int code, int sig)
{
	shell->syntax = 0;
	if (g_sig != sig)
		g_sig = sig;
	shell->exit_code = code;
}

void	write_exit(t_mini *shell, t_cmds *cmd)
{
	int	num;

	if (g_sig != 0)
		num = g_sig;
	else if (shell->syntax > 0)
		num = 258;
	else
		num = shell->exit_code;
	printf("%d: command not found\n", num);
	exit_code(shell, 127, 0);
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}

/*
checks the exit status for each command and exits the program with the
last child's exit code
*/
void	update_exitcode(t_mini *shell, t_cmds *cmds)
{
	int		exitcode;
	t_cmds	*command;

	command = cmds;
	while (command)
	{
		exitcode = 0;
		if (WIFEXITED(command->exit_status)
			&& WEXITSTATUS(command->exit_status) != 0)
		{
			exitcode = WEXITSTATUS(command->exit_status);
		}
		else if (command->valid == -1)
			exitcode = 127;
		else if (command->valid == -3)
			exitcode = 126;
		exit_code(shell, exitcode, 0);
		command = command->next;
	}
}
