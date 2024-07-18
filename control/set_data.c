/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:54:35 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/18 08:44:31 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	shell_lvl(t_mini *shell)
{
	int		i;
	t_env	*temp;

	temp = shell->env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, "SHLVL") == 0)
		{
			i = ft_atoi(temp->value);
			free(temp->value);
			if (i < 0)
				i = -1;
			temp->value = ft_itoa(i + 1);
			if (!temp->value)
				exit (1);
			return ;
		}
		temp = temp->next;
	}	
}

void	set_data(t_mini *shell, char **envp)
{
	shell->env = add_env(shell, envp);
	shell->env_p = NULL;
	shell->oldpwd = NULL;
	shell->pwd = getcwd(NULL, 0);
	shell->exit_code = 0;
	shell->saved_stdin = -1;
	shell->saved_stdout = -1;
	shell->syntax = 0;
	shell_lvl(shell);
}
