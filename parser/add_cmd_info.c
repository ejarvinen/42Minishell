/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:15:39 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/07 12:39:26 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmds_info(t_cmds **cmds)
{
	t_cmds	*cmd;
	int		nbr_of_cmds;

	nbr_of_cmds = ft_lstsize_pars(*cmds);
	cmd = *cmds;
	while (cmd)
	{
		cmd->commands = nbr_of_cmds;
		cmd = cmd->next;
	}
}

void	add_builtin_info(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (ft_strncmp(cmd->command[0], "echo", 4) == 0 && ft_strlen(cmd->command[0]) == 4)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "cd", 2) == 0 && ft_strlen(cmd->command[0]) == 2)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "pwd", 3) == 0 && ft_strlen(cmd->command[0]) == 3)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "export", 6) == 0 && ft_strlen(cmd->command[0]) == 6)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "unset", 5) == 0 && ft_strlen(cmd->command[0]) == 5)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "env", 3) == 0 && ft_strlen(cmd->command[0]) == 3)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "exit", 4) == 0 && ft_strlen(cmd->command[0]) == 4)
			cmd->builtin = 1;
		else if (ft_strncmp(cmd->command[0], "$?", 2) == 0 && ft_strlen(cmd->command[0]) == 2)
			cmd->builtin = 1;
		else
			cmd->builtin = 0;
		cmd = cmd->next;
	}
}
