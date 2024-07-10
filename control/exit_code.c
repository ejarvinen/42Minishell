/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:51:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 16:38:53 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_mini *shell, int code, int sig)
{
	shell->syntax = 0;
	if (g_sig != sig)
		g_sig = sig;
	shell->EXIT_CODE = code;
}

void	write_exit(t_mini *shell, t_cmds *cmd)
{
	int	num;

	if (g_sig != 0)
		num =  g_sig;
	else if (shell->syntax > 0)
		num = 258;
	else
		num = shell->EXIT_CODE;
	printf("%d: command not found\n", num);
	exit_code(shell, 127, 0);
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}
