/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/06 14:01:42 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	add fd for export print */

static int	new_strcmp(char *s1, char *s2)
{
	int	len;

	len = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[len] != '\0' && s2[len] != '\0')
	{
		if (s1[len] != s2[len])
			return (1);
		len++;
	}
	if (s1[len] == s2[len])
		return (0);
	return (1);
}

static void	find_key(t_env **env, char *str)
{
	t_env	*temp;
	int		i;

	temp = *env;
	while (temp != NULL)
	{
		i = new_strcmp(temp->key, str);
		if (i == 0)
			return ;
		if (1 == -1)
			exit (1);
		i = 0;
		while (temp->key[i] == str[i] && temp->key != '\0' && str != '\0')
			i++;
		if (temp->key[i] == '\0' && str[i] == '=')
		{
			edit_env(temp, str);
			return ;
		}
		temp = temp->next;
	}
	new_env(env, str);
}

void print_export(t_env *env)
{
	t_env	*temp;
	int		i;
	int		size;
	
	size = lstsize(env);
	i = 1;
	temp = env;
	while (size >= i)
	{
		if (temp->index == i)
		{
			if (new_strcmp(temp->key, "_") == 0)
			{}
			else if (temp->value == NULL && temp->equal == 1)
			 	printf("declare -x %s=\"\"\n", temp->key);
			else if (temp->value == NULL && temp->equal == 0)
				printf("declare -x %s\n", temp->key);
			else
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			i++;
			temp = env;
		}
		else
			temp = temp->next;
	}
}

// static void print_ll(t_env *env)
// {
// 	t_env *temp;

// 	temp = env;
// 	while (temp != NULL)
// 	{
// 		printf("key = %s\nvalue = %s\nindex = %i\n",temp->key, temp->value, temp->index);
// 		temp = temp->next;
// 	}
// }

void	export(t_env **env, char **str)
{
	int	i;
	t_env *temp;

	if (str[1] == NULL)
	{
		update_index(env);
		print_export(*env);
	}
	temp = *env;
	i = 1;
	if (str[i] != NULL)
	{
		while (str[i])
		{
			if (validity(str[i], "export") == 0)
				find_key(env, str[i]);
			i++;
		}
	}
}
