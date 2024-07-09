/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/09 11:36:38 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prep_for_exec(t_mini *shell)
{
	t_cmds	*temp;

	temp = shell->cmds;
	while (temp)
	{
		if (temp->heredoc != NULL)
			heredoc(shell, temp);
		temp = temp->next;
	}
	open_files(&shell->cmds);
	print_cmd_info(&shell->cmds);
	if (shell->cmds->command != NULL)
	{
		nonexistent_cmd(&shell->cmds);
		dot_cmd(&shell->cmds);
	}
	if ((shell->cmds->fd_infile == -1 && shell->cmds->heredoc == NULL)
		|| (shell->cmds->commands == 1 && shell->cmds->valid < 0 && shell->cmds->heredoc == NULL))
		return ;
	run_commands(shell);
}
