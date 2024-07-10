/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:51:49 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 17:52:57 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(t_mini *shell, char *test, char *path)
{
	if (test != NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		if (access(path, F_OK) == 0)
		{
			ft_putendl_fd(": Not a directory", 2);
		}
		else
			ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories", 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	exit_code(shell, 1, 0);
}

void	cd_more(t_mini *shell, char *message)
{
	ft_putendl_fd(message, 2);
	exit_code(shell, 1, 0);
}

void	childish(t_mini *shell)
{
	free_data(shell, NULL);
	exit(0);
}
