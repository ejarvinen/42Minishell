/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:29:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/12 15:05:57 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printer(t_env *node, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	if (node->equal == 0)
		ft_putendl_fd(node->key, fd);
	else
	{
		ft_putstr_fd(node->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		if (node->value != NULL)
			ft_putstr_fd(node->value, fd);
		ft_putendl_fd("\"", fd);
	}
}

void print_to_file(t_env *env, int fd)
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
			printer(temp, fd);
			temp = env;
			i++;
		}
		else
			temp = temp->next;
	}
}
