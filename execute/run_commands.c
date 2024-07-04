/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/03 11:28:39 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
