/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:15:39 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/16 11:13:12 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds the number of commands in the pipeline and initializes process if to -1
for each command
*/
void	add_cmds_info(t_cmds **cmds)
{
	t_cmds	*cmd;
	int		nbr_of_cmds;

	nbr_of_cmds = ft_lstsize_pars(*cmds);
	cmd = *cmds;
	while (cmd)
	{
		cmd->commands = nbr_of_cmds;
		cmd->c_pid = -1;
		cmd = cmd->next;
	}
}

/*
identifies and marks command a builtin
*/
void	add_builtin_info(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->command && ft_strcmp(cmd->command[0], "echo") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "cd") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "pwd") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "export") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "unset") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "env") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "exit") == 0)
			cmd->builtin = 1;
		else if (cmd->command && ft_strcmp(cmd->command[0], "$?") == 0)
			cmd->builtin = 1;
		else
			cmd->builtin = 0;
		cmd = cmd->next;
	}
}
