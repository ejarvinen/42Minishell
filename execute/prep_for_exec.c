/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 10:17:07 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	outfile_exists(t_cmds *cmd)
{
	int	index;
	
	if (cmd->outfile_name != NULL && ft_strcmp(cmd->outfile_name[0], "\0") != 0)
	{
		index = 0;
		while (cmd->outfile_name[index + 1])
			index++;
		return (index);
	}
	return (-1);
}

static int	write_hdoc_to_file(t_cmds *cmd, int outfile_index)
{
	int		fd;

	if (outfile_index != -1)
	{
		open_with_correct_flags(cmd, outfile_index);
		if (cmd->fd_outfile[outfile_index] < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->outfile_name[outfile_index]);
		}
		ft_putstr_fd(cmd->heredoc, cmd->fd_outfile[outfile_index]);
		//close(cmd->fd_outfile[outfile_index]);
	}
	else
	{
		fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: heredoc fail", 2);
			return (1);
		}
		ft_putstr_fd(cmd->heredoc, fd);
		close(fd);
	}
	return (0);
}

static int	heredoc_to_file(t_cmds *cmd, int outfile_index)
{
	char	**freeable;
	int		index;
	
	if (write_hdoc_to_file(cmd, outfile_index) > 0)
		return (1);
	if (outfile_index < 0)
	{
		freeable = cmd->command;
		index = get_index(cmd->command);
		cmd->command = (char **)malloc(sizeof(char *) * (index + 2));
		if (!cmd->command)
		{
			ft_putstr_fd("minishell: malloc fail", 2);
			return (1);
		}
		if (copy_filenames(cmd->command, freeable, ".temp", index) > 0)
		{
			ft_freearray(freeable);
			return (1);
		}
	}
	return (0);
}

static void	read_heredoc(t_mini *shell)
{
	t_cmds	*temp;
	int	outfile_index;

	temp = shell->cmds;
	while (temp)
	{
		if (temp->heredoc != NULL)
		{
			heredoc(shell, temp);
			outfile_index = outfile_exists(temp);
			if ((temp->heredoc && temp->fd_infile == 0) || (temp->command != NULL || (temp->command == NULL && outfile_index != -1)))
			{
				if (heredoc_to_file(temp, outfile_index) > 0)
				{
					ft_lstclear_pars(&shell->cmds);
					return ;
				}
			}
			else
			{
				ft_lstclear_pars(&shell->cmds);
				return ;
			}
		}
		temp = temp->next;
	}
}

void	minishell(t_mini *shell)
{
	read_heredoc(shell);
	open_files(&shell->cmds);
	if (!shell->cmds)
		return ;
	//print_cmd_info(&shell->cmds);
	if (shell->cmds->command != NULL)
	{
		nonexistent_cmd(&shell->cmds);
		dot_cmd(&shell->cmds);
	}
	run_commands(shell);
}
