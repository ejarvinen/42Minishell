/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:29:25 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 14:10:41 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_unset(t_env *unset)
{
	if (unset->value != NULL)
		free(unset->value);
	free(unset->key);
	free(unset);
}

void	ft_realunset(t_env **env, char *str)
{
	t_env	*unset;
	t_env	*prev;
	t_env	*next;

	unset = *env;
	if (unset->next == NULL)
	{
		free_unset(unset);
		*env = NULL;
		return ;
	}
	if (ft_strcmp(unset->key, str) == 0)
	{
		*env = unset->next;
		free_unset(unset);
		return ;
	}
	while (ft_strcmp(unset->next->key, str) != 0)
		unset = unset->next;
	prev = unset;
	unset = unset->next;
	next = unset->next;
	prev->next = next;
	free_unset(unset);
}

static void	almost_real_unset(t_cmds *cmd, t_mini *shell)
{
	t_env	*temp;
	int		i;

	i = 0;
	while (cmd->command[i] != NULL)
	{
		if (validity(cmd->command[i], "unset") != 0
			|| ft_strcmp("_", cmd->command[i]) == 0)
		{
			i++;
			continue ;
		}
		temp = shell->env;
		while (temp != NULL)
		{
			if (ft_strcmp(temp->key, cmd->command[i]) == 0)
			{
				ft_realunset(&shell->env, cmd->command[i]);
				break ;
			}
			else
				temp = temp->next;
		}
		i++;
	}
}

void	ft_unset(t_mini *shell, t_cmds *cmd)
{
	if (shell->env != NULL)
		almost_real_unset(cmd, shell);
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
	exit_code(shell, 0, 0);
}
