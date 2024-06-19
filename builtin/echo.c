/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:58 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/17 14:46:22 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_newline(char *str)
{
	int	i;

	i = 1;
	while (str[i] != NULL)
	{
		
	}	
}

void	ft_echo(t_mini *shell)
{
	int	nl;

	nl = check_newline(shell->cmds->command);
	if (shell->cmds->fd_outfile == 0)
		to_terminal(shell, shell->cmds->command, 0, nl);
	else
		to_file(shell, shell->cmds->command, shell->cmds->fd_outfile, nl);
}
