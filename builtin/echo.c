/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:58 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/02 11:18:37 by sataskin         ###   ########.fr       */
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

void	ft_echo(t_cmds *cmds)
{
	int	nl;
	int	i;
	int	fd;
	
	nl = check_newline(cmds->command);
	i = nl;
	fd = cmds->fd_outfile;
	while (cmds->command[i] != NULL)
	{
		if (nl == 1 && cmds->command[i + 1] == NULL)
		{
			nl = 0;
			ft_putendl_fd(cmds->command[i], fd);
		}
		else
		{
			ft_putstr_fd(cmds->command[i], fd);
			ft_putchar_fd(' ', fd);
		}
		i++;
	}
}
