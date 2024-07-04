/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:29:05 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/04 13:22:22 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* moro */

/* void	pwd(t_mini *shell)
{
	if (shell->cmds->fd_outfile == 0)
		printf("%s\n", shell->pwd);
	else
		ft_putendl_fd(shell->pwd, shell->cmds->fd_outfile);
} */

void	pwd(t_mini *shell, t_cmds *cmd)
{
	if (cmd->fd_outfile == 0)
		printf("%s\n", shell->pwd);
	else
		ft_putendl_fd(shell->pwd, cmd->fd_outfile);
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}
