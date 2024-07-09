/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:59:06 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/09 11:47:35 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
checks for an empty file and saves its fd into first command, opens outfile
and saves its fd into last command in cmds
*/
static int	open_outfile(t_cmds *cmd)
{
	int	index;
	int	error;
	
	if (cmd->fd_outfile == NULL)
	{
		cmd->fd_outfile = (int *)malloc(sizeof(int) * 1);
		if (!cmd->fd_outfile)
			return (1);
	}
	if (cmd->outfile_name == NULL)
		cmd->fd_outfile[0] = 1;
	else if (cmd->fd_infile == -1)
		cmd->fd_outfile[0] = -1;
	else
	{
		index = 0;
		error = 0;
		while (cmd->outfile_name[index])
		{
			if (cmd->fd_outfile[index] == -3)
				cmd->fd_outfile[index] = open(cmd->outfile_name[index], O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				cmd->fd_outfile[index] = open(cmd->outfile_name[index], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (cmd->fd_outfile[index] < 0 && error < 1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(cmd->outfile_name[index]);
				error = 1;
			}
			if (cmd->outfile_name[index + 1] == NULL)
				break ;
			close(cmd->fd_outfile[index]);
			index++;
		}
		if (cmd->outfile_name[index] == NULL)
			index--;
		error = 0;
		while (error < index)
		{
			if (cmd->fd_outfile[error] > -1)
				close(cmd->fd_outfile[error]);
			error++;
		}
		cmd->fd_outfile[0] = cmd->fd_outfile[index];
	}
	return (0);
}

/*
checks if infile exists
*/
/* static void	open_infile(t_cmds *cmd)
{
	int	index;
	int error;
	
	if (cmd->infile_name == NULL)
		cmd->fd_infile = 0;
	else
	{
		index = 0;
		error = 0;
		while (cmd->infile_name[index])
		{
			if (ft_strcmp(cmd->infile_name[index], "heredoc") != 0)
			{
				cmd->fd_infile = open(cmd->infile_name[index], O_RDONLY, 0666);
				if (cmd->fd_infile < 0 && error < 1)
				{
					ft_putstr_fd("minishell: ", 2);
					perror(cmd->infile_name[index]);
					error = 1;
				}
				if (cmd->infile_name[index + 1] == NULL)
					break ;
				close(cmd->fd_infile);
			}
			index++;
		}
		if (ft_strcmp(cmd->infile_name[index - 1], "heredoc") == 0)
			cmd->fd_infile = 0;
	}
} */

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

/*
opens any infiles and outfiles specified for each command
*/
void	open_files(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		//open_infile(cmd);
		if (open_outfile(cmd) > 0)
		{
			ft_lstclear_pars(cmds);
			return ;
		}
		cmd = cmd->next;
	}
}
