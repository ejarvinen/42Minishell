/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 06:59:51 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 09:25:35 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
constructs a full command path
*/
char	*full_path(char *path, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (full_path);
}

/*
checks whether the calling process can access path for a given command;
returns index for accessible path in paths, -1 if path not found/command
doesn't exist, -2 if given command is an absolute path that is executable,
-3 if path is accessible but not executable
*/
static int	path_checker(char *command, char **paths)
{
	char	*path;
	int		index;

	index = 0;
	while (paths[index])
	{
		path = full_path(paths[index], command);
		if (!path)
			return (-4);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				free(path);
				return (index);
			}
			free(path);
			return (-3);
		}
		free(path);
		index++;
	}
	return (-1);
}

/*
checks for NULL command, absolute path and executability
*/
static int	validate_command(char *command, char **paths)
{
	if (command == NULL)
		return (-1);
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (-2);
	}
	return (path_checker(command, paths));
}

static int	add_path(t_cmds *cmd, char **paths, int path_index)
{
	if (path_index > -1)
		cmd->path = full_path(paths[path_index], cmd->command[0]);
	else if (path_index == -2)
		cmd->path = ft_strdup(cmd->command[0]);
	else
		cmd->path = ft_strdup("0");
	if (!cmd->path)
		return (1);
	cmd->valid = path_index;
	return (0);
}

/*
finds allowed paths and splits them into 2D array
*/
static char	**path_finder(t_env **envs)
{
	int		index;
	char	**env;
	char	**paths;

	env = ltoa(*envs);
	if (!env)
		return (NULL);
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], "PATH=", 5) == 0)
			break ;
		index++;
	}
	if (!env[index])
	{
		ft_putstr_fd("minishell: no PATH environment variable specified\n", 2);
		free_array(env);
		return (NULL);
	}
	paths = ft_split(env[index] + 5, ':');
	if (!paths)
	{
		perror("minishell");
		free_array(env);
		return (NULL);
	}
	return (paths);
}

void	validate_commands(t_cmds **cmds, t_env **envs)
{
	t_cmds	*cmd;
	char	**paths;
	int	path_index;

	cmd = *cmds;
	paths = path_finder(envs);
	if (!paths)
	{
		ft_lstclear_pars(cmds);
		return ;
	}
	while (cmd)
	{
		if (cmd->builtin != 1)
		{
			path_index = validate_command(cmd->command[0], paths);
			if (path_index == -4 || add_path(cmd, paths, path_index) > 0)
			{
				free_array(paths);
				ft_lstclear_pars(cmds);
				return ;
			}
		}
		/*else
			cmd->valid = 1;*/
		cmd = cmd->next;
	}
	free_array(paths);
}
