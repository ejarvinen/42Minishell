/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:58 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/06 11:41:59 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	protection(char **str)
{
	int	i;

	i = 1;
	if (str[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else
	{
		while (str[i] != NULL && ft_strcmp(str[i], "-n") == 0)
			i++;
		if (str[i] == NULL)
			return (1);
	}
	return (0);
}

static int	check_newline(char **str)
{
	int	i;

	i = 1;
	while (ft_strcmp(str[i], "-n") == 0)
		i++;
	return (i);
}

/* void	ft_echo(t_cmds *cmds) old version before child processes
{
	int	nl;
	int	i;
	int	fd;
	
	if (protection(cmds->command) != 0)
		return ;
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
		else if (cmds->command[i + 1] != NULL)
		{
			ft_putstr_fd(cmds->command[i], fd);
			ft_putchar_fd(' ', fd);
		}
		else
			ft_putstr_fd(cmds->command[i], fd);
		i++;
	}
} */

/* void	ft_echo(t_mini *shell, t_cmds *cmds) !! sample version that works with piping !!
{
	int	index;
	
	if (protection(cmds->command) != 0)
	{
		if (cmds->c_pid == -1)
			return ;
		else
		{
			free_data(shell, NULL);
			exit(1);
		}
	}
	index = 1;
	while (cmds->command[index])
	{
		printf("%s ", cmds->command[index]);
		index++;
	}
	printf("\n");
	if (cmds->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
} */

void	ft_echo(t_mini *shell, t_cmds *cmds)
{
	int	nl;
	int	i;
	int	fd;
	
	if (protection(cmds->command) != 0)
	{
		if (cmds->c_pid == -1)
			return ;
		else
		{
			free_data(shell, NULL);
			exit(1);
		}
	}
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
		else if (cmds->command[i + 1] != NULL)
		{
			ft_putstr_fd(cmds->command[i], fd);
			ft_putchar_fd(' ', fd);
		}
		else
			ft_putstr_fd(cmds->command[i], fd);
		i++;
	}
	if (cmds->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}
