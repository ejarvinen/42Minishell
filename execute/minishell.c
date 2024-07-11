/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:12:23 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 13:24:57 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell(t_mini *shell)
{
	read_heredoc(shell);
	open_files(shell, &shell->cmds);
	if (!shell->cmds)
		return ;
	if (shell->cmds->command != NULL)
	{
		nonexistent_cmd(&shell->cmds);
		dot_cmd(&shell->cmds);
	}
	run_commands(shell);
}
