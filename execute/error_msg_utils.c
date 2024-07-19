/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:52:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/19 11:29:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
counts the number of forward slashes in command
*/
int	is_dir(char *command)
{
	int	slash;
	int	index;

	index = 0;
	slash = 0;
	while (command[index])
	{
		if (command[index] == 47)
			slash++;
		index++;
	}
	return (slash);
}

/*
prints a is directory error message
*/
void	print_dirmsg(t_cmds *cmd, t_mini *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->command[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	exit_code(shell, 126, 0);
	cmd->valid = -1;
}
