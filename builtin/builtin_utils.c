/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:05:27 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/18 12:46:16 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	delimiter(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	if (c == '\n' || c == '\0')
		return (1);
	return (0);
}

t_env	*hdoc_key(char *str, int index, t_env *env)
{
	t_env	*temp;
	int		loop;
	int		key;

	temp = env;
	index++;
	while (temp != NULL)
	{
		key = 0;
		loop = index;
		while (temp->key[key] == str[loop] && str[loop] != '\0')
		{
			loop++;
			key++;
		}
		if (temp->key[key] == '\0' && delimiter(str[loop]) == 1)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*retrieve_key(t_env *env, char *str)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, str) == 0)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}
