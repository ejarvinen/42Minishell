/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 08:25:24 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	write_hdoc_to_file(t_cmds *cmd)
{
	int		fd;

	fd = open(".temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: heredoc fail", 2);
		return (1);
	}
	ft_putstr_fd(cmd->heredoc, fd);
	close(fd);
	return (0);
}

static int	heredoc_to_file(t_cmds *cmd)
{
	char	**freeable;
	int		index;

	if (write_hdoc_to_file(cmd) > 0)
		return (1);
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
	return (0);
}

static void	read_heredoc(t_mini *shell)
{
	t_cmds	*temp;

	temp = shell->cmds;
	while (temp)
	{
		if (temp->heredoc != NULL)
		{
			heredoc(shell, temp);
			if (temp->heredoc && temp->fd_infile == 0 && temp->command != NULL)
			{
				if (heredoc_to_file(temp) > 0)
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
