/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:33:05 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 18:40:35 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	make_new(t_mini *shell, t_env *new, char *str)
{
	new->key = get_key(shell, str);
	new->value = get_value(shell, str);
	new->equal = 1;
}

void	edit_env(t_mini *shell, t_env *node, char *str)
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
	node->value = get_value(shell, str);
}

void	new_env(t_mini *shell, t_env **env, char *str)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		free_and_exit(shell, "minishell: malloc fail\n");
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (str[i] == '\0')
	{
		new->key = ft_strdup(str);
		if (!new->key)
			free_and_exit(shell, "minishell: malloc fail\n");
		new->value = NULL;
		new->equal = 0;
	}
	else
		make_new(shell, new, str);
	new->index = -1;
	new->next = NULL;
	ft_lstadd_back_mini(env, new);
}
