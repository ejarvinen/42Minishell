/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_pt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:00:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/07 13:27:17 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env *temp;

	if (env == NULL)
		return ;
	temp = env->next;
	while (env != NULL)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		temp = env->next;
		free(env);
		env = temp;
	}
}

void	*ft_freearray(char **array)
{
	int i = 0;
	
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	free_data(t_mini *shell)
{
	free_env(shell->env);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->cmds)
		ft_lstclear_pars(&shell->cmds, free);
}
