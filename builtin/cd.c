/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:39:25 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/22 17:09:51 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_pwd(t_mini *shell, t_env *old, t_env *new)
{
	if (old)
	{
		if (old->value)
			free(old->value);
		old->value = ft_strdup(shell->pwd);
		if (!old->value)
			free_and_exit(shell, "minishell: malloc fail");
		old->equal = 1;
	}
	if (new)
	{
		if (new->value)
			free(new->value);
		new->value = getcwd(NULL, 0);
		if (!new->value)
			new->value = ft_strjoin(old->value, "/..");
		if (!new->value)
			free_and_exit(shell, "minishell: malloc fail");
		new->equal = 1;
	}
}

static void	reset_data(t_mini *shell)
{
	if (shell->oldpwd)
		free(shell->oldpwd);
	shell->oldpwd = ft_strdup(shell->pwd);
	if (!shell->oldpwd)
		free_and_exit(shell, "minishell: malloc fail");
	free(shell->pwd);
	shell->pwd = getcwd(NULL, 0);
	if (!shell->pwd)
		shell->pwd = ft_strjoin(shell->oldpwd, "/..");
	if (!shell->pwd)
		free_and_exit(shell, "minishell: malloc fail");
}

static void	go_home(t_mini *shell, t_env *env)
{
	t_env	*temp;
	t_env	*new;
	t_env	*old;

	new = env;
	old = env;
	temp = retrieve_key(env, "HOME");
	if (temp != NULL && chdir(temp->value) == 0)
	{
		while (new != NULL && ft_strcmp(new->key, "PWD") != 0)
			new = new->next;
		while (old != NULL && ft_strcmp(old->key, "OLDPWD") != 0)
			old = old->next;
		set_pwd(shell, old, new);
		reset_data(shell);
		exit_code(shell, 0, 0);
		return ;
	}
	else if (temp == NULL)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else
		perror("minishell: cd");
	exit_code(shell, 1, 0);
}

static void	cd_path(char *path, t_mini *shell)
{
	t_env	*new;
	t_env	*old;
	char	*test;

	new = shell->env;
	old = shell->env;
	if (chdir(path) == 0)
	{
		test = getcwd(NULL, 0);
		if (test == NULL)
			cd_error(shell, test, path);
		else
			free(test);
		while (new != NULL && ft_strcmp(new->key, "PWD") != 0)
			new = new->next;
		while (old != NULL && ft_strcmp(old->key, "OLDPWD") != 0)
			old = old->next;
		set_pwd(shell, old, new);
		reset_data(shell);
		exit_code(shell, 0, 0);
	}
	else
		cd_error(shell, "TEST", path);
}

void	ft_cd(t_mini *shell, t_cmds *cmd)
{
	char	*test;
	int		i;

	i = 0;
	while (cmd->command[i] != NULL)
		i++;
	if (i > 2)
		cd_more(shell, "minishell: cd: too many arguments");
	else if (cmd->command[1] == NULL)
		go_home(shell, shell->env);
	else
	{
		test = getcwd(NULL, 0);
		if (test != NULL || cmd->command[1][0] == '/'
			|| ft_strcmp(cmd->command[1], ".")  != 0)
		{
			cd_path(cmd->command[1], shell);
			free(test);
		}
		else
			cd_error(shell, test, cmd->command[1]);
	}
	if (cmd->c_pid != -1)
		childish(shell);
}
