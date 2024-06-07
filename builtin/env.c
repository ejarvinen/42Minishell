/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:49:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/05/31 13:56:29 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	t_env	*temp;
	
	temp = env;
	while(temp)
	{
		if (temp->equal == 1 && temp->value != NULL)
			printf("%s=%s\n", temp->key, temp->value);
		else if (temp->equal)
			printf("%s=", temp->key);
		temp = temp->next;
	}
	return (0);
}