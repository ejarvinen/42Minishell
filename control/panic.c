/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:00:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 10:44:30 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_freearray(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	panic(t_mini *shell, int *pipefds, char **envs, int error_code)
{
	if (pipefds)
	{
		close_pipes(pipefds);
		free(pipefds);
	}
	if (envs)
		ft_freearray(envs);
	free_data(shell, NULL);
	exit(error_code);
}

void	free_data(t_mini *shell, char *message)
{
	restore_fds(shell);
	free_env(shell->env);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->cmds)
	{
		close_files(&shell->cmds);
		ft_lstclear_pars(&shell->cmds);
	}
	if (message != NULL)
		printf("%s", message);
}

void	free_and_exit(t_mini *shell, char *message)
{
	//if (shell->pipefds)
	//{
	//	close_pipes(pipefds);
	//	free(pipefds);
	//}
	free_data(shell, message);
	exit (1);
}
