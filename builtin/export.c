/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/19 16:59:25 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	new_strcmp(char *s1, char *s2)
{
	int	len;

	len = 0;
	if (!s1 || !s2)
		return (1);
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

static void	find_key(t_mini *shell, t_env **env, char *str)
{
	t_env	*temp;
	int		i;

	temp = *env;
	while (temp != NULL)
	{
		i = new_strcmp(temp->key, str);
		if (i == 0)
			return ;
		i = 0;
		while (temp->key[i] != '\0' && str[i] != '\0' && temp->key[i] == str[i])
			i++;
		if (temp->key[i] == '\0' && str[i] == '=')
		{
			edit_env(shell, temp, str);
			return ;
		}
		temp = temp->next;
	}
	new_env(shell, env, str);
}

static void	printer(t_env *temp)
{
	if (temp->value == NULL && temp->equal == 1)
		printf("declare -x %s=\"\"\n", temp->key);
	else if (temp->value == NULL && temp->equal == 0)
		printf("declare -x %s\n", temp->key);
	else
		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
}

void	print_export(t_env *env)
{
	t_env	*temp;
	int		i;
	int		size;

	size = lstsize(env);
	i = 1;
	temp = env;
	while (temp != NULL && size >= i)
	{
		if (temp->index == i)
		{
			if (new_strcmp(temp->key, "_") != 0)
				printer(temp);
			i++;
			temp = env;
		}
		else
			temp = temp->next;
	}
}

void	export(t_mini *shell, t_cmds *cmd)
{
	int	i;
	int	prob;

	i = 1;
	prob = 0;
	if (cmd->command[i] == NULL && shell->env != NULL)
	{
		update_index(&shell->env);
		print_export(shell->env);
	}
	else if (cmd->command[i] != NULL)
	{
		while (cmd->command[i])
		{
			if (validity(cmd->command[i], "export") == 0)
				find_key(shell, &shell->env, cmd->command[i]);
			else
				prob = 1;
			i++;
		}
	}
	if (cmd->c_pid != -1)
		childish(shell);
	exit_code(shell, prob, 0);
}
