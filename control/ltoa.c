/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:22:04 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/08 08:32:01 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ltoa_lstsize(t_env *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		if (lst->value != NULL)
			len++;
		lst = lst->next;
	}
	return (len);
}

static char	*get_string(char *key, char *value)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(key);
	j = 0;
	new = (char *)malloc(sizeof(char) * (i + ft_strlen(value) + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (key[i] != '\0')
	{
		new[i] = key[i];
		i++;
	}
	new[i] = '=';
	i++;
	while (value[j] != '\0')
	{
		new[i] = value[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ltoa(t_env *env)
{
	t_env	*temp;
	int		len;
	int		i;
	char	**ret;
	
	len = ltoa_lstsize(env);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	temp = env;
	i = 0;
	while (temp != NULL)
	{
		if (temp->value != NULL)
		{
			ret[i] = get_string(temp->key, temp->value);
			if (!ret[i])
			{
				ft_freearray(ret);
				return (NULL);
			}
			i++;
		}
		temp = temp->next;
	}
	ret[len] = NULL;
	return (ret);
}
