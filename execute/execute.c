/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:34:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/20 14:03:46 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	safe_to_run(t_cmds *cmds)
{
	if (cmds->command == NULL
		|| ((cmds->fd_infile == -1 || cmds->valid == -1)
			&& cmds->heredoc == NULL) || cmds->fd_outfile[0] < 0)
		return (0);
	return (1);
}

/*
sets up pipes and redirections according to command type and runs
a builtin or execve accordingly
*/
void	execute(t_mini *shell, t_cmds *cmd)
{
	if (cmd->id == 0)
		first_command(shell, cmd);
	else if (cmd->id == cmd->commands - 1)
		last_command(shell, cmd);
	else
		set_pipes(shell, cmd);
	if (cmd->builtin == 1)
	{
		check_builtin(shell, cmd);
	}
	else
	{
		if (execve(cmd->path, cmd->command, shell->env_p) == -1)
			panic(shell, 126);
	}
}
