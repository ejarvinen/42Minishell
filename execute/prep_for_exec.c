/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/05 12:15:59 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_for_exec(t_mini *shell)
{
	open_files(&shell->cmds);
	//print_cmd_info(&shell->cmds);
	nonexistent_cmd(&shell->cmds);
	dot_cmd(&shell->cmds);
	if (shell->cmds->fd_infile == -1 || (shell->cmds->commands == 1 && shell->cmds->valid < 0))
		return ;
	run_commands(shell);
}
