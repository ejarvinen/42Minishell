/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:05:27 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/19 12:11:46 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_strcmp(char *temp, char *str)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	if (!temp || !str)
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		i--;
	while (str[i] && temp[t])
	{
		if (str[i] != temp[t])
			return (1);
		i++;
		t++;
	}
	if (str[i] == '\0' && temp[t] == '\0')
		return (0);
	return (1);
}

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
