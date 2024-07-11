/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:29:05 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 14:10:41 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_mini *shell, t_cmds *cmd)
{
	printf("%s\n", shell->pwd);
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
	exit_code(shell, 0, 0);
}
