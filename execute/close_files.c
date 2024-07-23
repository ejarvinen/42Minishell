/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:26:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 09:28:17 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_temp(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->heredoc != NULL)
		{
			if (access(".temp", F_OK) == 0)
			{
				unlink(".temp");
				break ;
			}	
		}
		cmd = cmd->next;
	}
}

/*
closes any infiles and outfiles that might be open for each command
*/
void	close_files(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->fd_infile > 1)
			close(cmd->fd_infile);
		if (cmd->fd_outfile[0] > 1)
			close(cmd->fd_outfile[0]);
		cmd = cmd->next;
	}
}
