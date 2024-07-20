/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 06:59:51 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/20 12:45:03 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
saves path info to cmd according to given path_index: constructs full path
for positve indexes; for index -2 saves command as absolute path; for other
indexes strdups an empty string
*/
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
prints ppath_finder errors according to err_code
*/
static char	**print_error(char **env, int err_code)
{
	if (err_code == 1)
		ft_putstr_fd("minishell: no PATH environment variable specified\n", 2);
	else if (err_code == 2)
		ft_putstr_fd("minishell: malloc fail\n", 2);
	ft_freearray(env);
	return (NULL);
}

/*
finds allowed paths and splits them into 2D array
*/
static char	**path_finder(t_env **envs)
{
	int		index;
	char	**env;
	char	**paths;

	env = ltoa(envs);
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
		return (print_error(env, 1));
	paths = ft_split(env[index] + 5, ':');
	if (!paths)
		return (print_error(env, 2));
	ft_freearray(env);
	return (paths);
}

/*
checks and finds valid paths for non-builtin commands,
marks builtins valid by default
*/
void	validate_commands(t_mini *shell, t_cmds *cmd)
{
	char	**paths;
	int		path_index;

	paths = NULL;
	if (cmd->builtin != 1)
	{
		paths = path_finder(&shell->env);
		if (!paths)
		{
			ft_lstclear_pars(&shell->cmds);
			return ;
		}
		path_index = validate_command(cmd->command[0], paths);
		if (path_index == -4 || add_path(cmd, paths, path_index) > 0)
		{
			ft_freearray(paths);
			ft_lstclear_pars(&shell->cmds);
			return ;
		}
		ft_freearray(paths);
	}
	else
		cmd->valid = 1;
}
