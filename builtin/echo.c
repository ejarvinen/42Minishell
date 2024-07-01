/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:58 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/01 14:48:52 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_newline(char **str)
{
	int	i;

	i = 1;
	while (ft_strcmp(str[i], "-n") == 0)
		i++;
	return (i);
}

void	ft_echo(t_mini *shell)
{
	int	nl;
	int	i;
	int	fd;
	
	nl = check_newline(shell->cmds->command);
	i = nl;
	fd = shell->cmds->fd_outfile;
	while (shell->cmds->command[i] != NULL)
	{
		if (nl == 1)
			ft_putendl_fd(shell->cmds->command[i], fd);
		else
			ft_putstr_fd(shell->cmds->command[i], fd);
		i++;
	}
}
