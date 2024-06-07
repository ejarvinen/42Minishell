/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:33:05 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/06 12:12:05 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	edit_env(t_env *node, char *str)
{
	int	i;

	i = 0;
	node->equal = 1;
	while (str[i] != '=')
		i++;
	if (ft_strcmp(node->key, "_") == 0)
		return ;
	if (node->value != NULL)
		free(node->value);
	node->value = get_value(str);
}

void	new_env(t_env **env, char *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	//malloc check
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
	{
		new->key = ft_strdup(str);
		new->value = NULL;
		new->equal = 0;
	}
	else
	{
		new->key = get_key(str);
		new->value = get_value(str);
		new->equal = 1;
	}
	new->index = -1;
	new->next = NULL;
	ft_lstadd_back_mini(env, new);
}
