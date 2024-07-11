/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:08:56 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 10:53:29 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_mini(t_env **lst, t_env *new)
{
	t_env	*node;

	node = *lst;
	if (!new)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

char	*get_key(t_mini *shell, char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=' && str)
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		free_and_exit(shell, "minishell: malloc fail\n");
	key[i] = '\0';
	i--;
	while (i >= 0)
	{
		key[i] = str[i];
		i--;
	}
	return (key);
}

char	*get_value(t_mini *shell, char *envp)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = 0;
	while (envp[i] != '=' && envp)
		i++;
	if (envp[i] == '\0')
		return (NULL);
	len = ft_strlen(envp);
	value = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!value)
		free_and_exit(shell, "minishell: malloc fail\n");
	len = 0;
	i++;
	while (envp[i] != '\0')
	{
		value[len] = envp[i];
		i++;
		len++;
	}
	value[len] = '\0';
	return (value);
}

void	add_input(t_mini *shell, t_env *node, char *envp)
{
	node->key = get_key(shell, envp);
	node->value = get_value(shell, envp);
	node->equal = 1;
	node->index = -1;
}

t_env	*add_env(t_mini *shell, char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			free_and_exit(shell, "minishell: malloc fail\n");
		add_input(shell, new, envp[i]);
		new->next = NULL;
		ft_lstadd_back_mini(&env, new);
		i++;
	}
	return (env);
}
