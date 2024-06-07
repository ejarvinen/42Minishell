/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:00:16 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/06 11:37:58 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_env *lst)
{
	int	len;

	len = 1;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_env	*find_next(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp->next != NULL)
	{
		if (temp->index == -1)
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

void	change_index(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if (temp->next == NULL)
		temp->index = 1;
	else
	{
		while (temp != NULL)
		{
			temp->index = -1;
			temp = temp->next;
		}
	}
}

void	update_index(t_env **env)
{
	int		index;
	t_env	*temp;
	t_env	*max_val;

	change_index(env);
	index = lstsize(*env);
	temp = *env;
	max_val = *env;
	if (index < 2)
		return ;
	while (index > 0)
	{
		temp = temp->next;
		if (ft_strcmp(temp->key, max_val->key) > 0 && temp->index == -1)
			max_val = temp;
		if (temp->next == NULL)
		{
			max_val->index = index;
			index--;
			max_val = find_next(*env);
			temp = *env;
		}
	}
}
