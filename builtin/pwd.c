/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:29:05 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/13 10:30:17 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* moro */

void	pwd(t_mini *shell)
{
	if (shell->cmds->fd_outfile == 0)
		printf("%s\n", shell->pwd);
	else
		ft_putendl_fd(shell->pwd, shell->cmds->fd_outfile);
}
