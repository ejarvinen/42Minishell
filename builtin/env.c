/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:49:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/05 14:15:07 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mini *shell, t_cmds *cmd)
{
	t_env	*temp;
	
	temp = shell->env;
	while(temp)
	{
		if (temp->equal == 1)
		{
			ft_putstr_fd(temp->key, cmd->fd_outfile);
			ft_putstr_fd("=", cmd->fd_outfile);
			if (temp->value != NULL)
				ft_putstr_fd(temp->value, cmd->fd_outfile);
			ft_putchar_fd('\n', cmd->fd_outfile);
		}
		temp = temp->next;
	}
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
	return (0);
}
