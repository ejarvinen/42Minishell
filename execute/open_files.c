/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:59:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 10:40:50 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_with_correct_flags(t_cmds *cmd, int index)
{
	if (cmd->fd_outfile[index] == -3)
		cmd->fd_outfile[index] = open(cmd->outfile_name[index],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (cmd->fd_outfile[index] == -2)
		cmd->fd_outfile[index] = open(cmd->outfile_name[index],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

static int	open_outfiles(t_mini *shell, t_cmds *cmd)
{
	int	index;
	int	error;

	index = 0;
	error = 0;
	while (cmd->outfile_name[index])
	{
		open_with_correct_flags(cmd, index);
		if (cmd->fd_outfile[index] < 0 && error < 1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->outfile_name[index]);
			exit_code(shell, 1, 0);
			error = 1;
		}
		if (cmd->outfile_name[index + 1] == NULL)
			break ;
		close(cmd->fd_outfile[index]);
		index++;
	}
	if (cmd->outfile_name[index] == NULL)
		index--;
	return (index);
}

/*
checks for an empty file and saves its fd into first command, opens outfile
and saves its fd into last command in cmds
*/
static int	open_outfile(t_mini *shell, t_cmds *cmd)
{
	int	index;

	if (cmd->fd_outfile == NULL)
	{
		cmd->fd_outfile = (int *)malloc(sizeof(int) * 1);
		if (!cmd->fd_outfile)
		{
			parser_error("malloc fail");
			return (1);
		}
	}
	if (cmd->outfile_name == NULL)
		cmd->fd_outfile[0] = 1;
	else if (cmd->fd_infile == -1)
		cmd->fd_outfile[0] = -1;
	else
	{
		index = open_outfiles(shell, cmd);
		cmd->fd_outfile[0] = cmd->fd_outfile[index];
	}
	return (0);
}

/*
opens any infiles and outfiles specified for each command
*/
void	open_files(t_mini *shell, t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->infile_name == NULL)
			cmd->fd_infile = 0;
		else if (ft_strcmp(cmd->infile_name, ".temp") == 0)
		{
			cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
			if (cmd->fd_infile < 0)
				ft_putstr_fd("minishell: heredoc fail", 2);
		}
		if (open_outfile(shell, cmd) > 0)
		{
			ft_lstclear_pars(cmds);
			return ;
		}
		cmd = cmd->next;
	}
}
