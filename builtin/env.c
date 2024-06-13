/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:49:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/13 10:45:23 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mini *shell)
{
	t_env	*temp;
	
	temp = shell->env;
	while(temp)
	{
		if (temp->equal == 1)
		{
			ft_putstr_fd(temp->key, shell->cmds->fd_outfile);
			ft_putstr_fd("=", shell->cmds->fd_outfile);
			if (temp->value != NULL)
				ft_putstr_fd(temp->value, shell->cmds->fd_outfile);
			ft_putchar_fd('\n', shell->cmds->fd_outfile);
		}
		temp = temp->next;
	}
	return (0);
}
