/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:49:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 13:58:52 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_mini *shell, t_cmds *cmd)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		if (temp->equal == 1)
		{
			if (temp->value != NULL)
				printf("%s=%s\n", temp->key, temp->value);
			else
				printf("%s=\n", temp->key);
		}
		temp = temp->next;
		exit_code(shell, 0, 0);
	}
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}
