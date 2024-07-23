/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:58 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/23 10:05:35 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_newline(char **str)
{
	int	i;
	int	ind;

	i = 1;
	while (str[i] != NULL)
	{
		ind = 1;
		if (str[i][0] != '-')
			return (i);
		while (str[i][ind] == 'n')
			ind++;
		if (str[i][ind] != '\0')
			return (i);
		i++;
	}
	return (i);
}

static void	echo_to_terminal(t_mini *shell, t_cmds *cmds)
{
	int	i;
	int	nl;

	nl = check_newline(cmds->command);
	i = nl;
	while (cmds->command[i] != NULL)
	{
		if (nl == 1 && cmds->command[i + 1] == NULL)
			printf("%s\n", cmds->command[i]);
		else if (nl != 1 && cmds->command[i + 1] == NULL)
			printf("%s", cmds->command[i]);
		else if (cmds->command[i] != NULL && cmds->command[i][0] != '\0')
			printf("%s ", cmds->command[i]);
		else if (cmds->command[i][0] != '\0')
			printf("%s", cmds->command[i]);
		i++;
	}
	exit_code(shell, 0, 0);
}

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

void	ft_echo(t_mini *shell, t_cmds *cmds)
{
	if (protection(cmds->command) != 0)
	{
		exit_code(shell, 1, 0);
		if (cmds->c_pid == -1)
			return ;
		else
		{
			free_data(shell, NULL);
			exit(1);
		}
	}
	echo_to_terminal(shell, cmds);
	if (cmds->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
}
