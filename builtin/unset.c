/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:29:25 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/06 12:05:15 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_realunset(t_env **env, char *str)
{
	t_env	*unset;
	t_env	*prev;
	t_env	*next;

	unset = *env;
	while (ft_strcmp(unset->next->key, str) != 0)
		unset = unset->next;
	prev = unset;
	unset = unset->next;
	next = unset->next;
	prev->next = next;
	if (unset->value != NULL)
		free(unset->value);
	free(unset->key);
	free(unset);
}

void	ft_unset(t_env **env, char **str)
{
	t_env	*temp;
	int		i;

	i = 1;
	while (str[i] != NULL)
	{
		if (validity(str[i], "unset") != 0 || ft_strcmp("_", str[i]) == 0)
		{
			i++;
			continue ;
		}
		temp = *env;
		while (temp != NULL)
		{
			if (ft_strcmp(temp->key, str[i]) == 0)
			{
				printf("found key\n");
				ft_realunset(env, str[i]);
				break ;
			}
			else
				temp = temp->next;
		}
		i++;
	}
}
