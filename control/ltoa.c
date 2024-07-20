/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:22:04 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/20 15:55:25 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ltoa_lstsize(t_env **lst)
{
	int		len;
	t_env	*temp;

	len = 0;
	if (!lst)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		if (temp->value != NULL)
			len++;
		temp = temp->next;
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

static char	*make_ret(char **ret, int i, t_env *temp)
{
	if (temp->key != NULL)
	{
		ret[i] = get_string(temp->key, temp->value);
		if (!ret[i])
		{
			ft_freearray(ret);
			return (NULL);
		}
	}
	return ("yay");
}

char	**ltoa(t_env **env)
{
	t_env	*temp;
	int		len;
	int		i;
	char	**ret;

	if (env == NULL)
		return (NULL);
	len = ltoa_lstsize(env);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	temp = *env;
	i = 0;
	while (temp != NULL)
	{
		if (temp->value)
		{
			if (make_ret(ret, i, temp) == NULL)
				return (NULL);
			i++;
		}
		temp = temp->next;
	}
	ret[i] = NULL;
	return (ret);
}
