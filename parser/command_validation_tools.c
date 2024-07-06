/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:09:02 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 14:09:49 by emansoor         ###   ########.fr       */
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
int	validate_command(char *command, char **paths)
{
	if (command == NULL || ft_strncmp(command, "\0", 1) == 0)
		return (-1);
	if (access(command, F_OK) == 0)
	{
		if (access(command, X_OK) == 0)
			return (-2);
	}
	return (path_checker(command, paths));
}
