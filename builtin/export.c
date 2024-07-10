/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:20:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 15:52:27 by emansoor         ###   ########.fr       */
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
		while (temp->key[i] == str[i] && temp->key[i] != '\0' && str[i] != '\0')
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

/* void	export(t_env **env, char **str, int fd)
{
	int	i;
	
	if (fd < 0)
		return ;
	if (str[1] == NULL)
	{
		update_index(env);
		if (fd == 0)
			print_export(*env);
		else
			print_to_file(*env, fd);
	}
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
} */

void	export(t_mini *shell, t_cmds *cmd)
{
	int	i;
	
	i = 1;
	if (cmd->fd_outfile[0] < 0)
	{
		if (cmd->c_pid == -1)
			return ;
		else
		{
			free_data(shell, NULL);
			exit(1);
		}
	}
	if (cmd->command[i] == NULL)
	{
		if (shell->env != NULL)
		{
			update_index(&shell->env);
			print_export(shell->env);
		}
	}
	else if (cmd->command[i] != NULL)
	{
		while (cmd->command[i])
		{
			if (validity(cmd->command[i], "export") == 0)
				find_key(&shell->env, cmd->command[i]);
			i++;
		}
	}
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}

