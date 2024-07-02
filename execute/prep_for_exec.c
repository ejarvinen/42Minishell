/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 11:53:05 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_for_exec(t_mini *shell)
{
	open_files(&shell->cmds);
	//print_cmd_info(&shell->cmds);
	nonexistent_cmd(&shell->cmds);
	dot_cmd(&shell->cmds);
	if (shell->cmds->fd_infile == -1)
		return ;
	run_commands(shell);
}
