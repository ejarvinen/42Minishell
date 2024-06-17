/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:49:29 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/17 07:51:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
prints bash like error message for incomplete . arguments
*/
static void	print_usage_msg(char *command)
{
	if (ft_strncmp(command, ".", 1) == 0 && ft_strlen(command) == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": usage: . filename [arguments]\n", 2);
	}
	else if (ft_strncmp(command, "\0", 2) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

/*
prints error messages by command type
*/
static void	print_error_msg(char *command, int type)
{
	int	dir;
	
	if (type == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (type == -2)
	{
		dir = open(command, O_DIRECTORY);
		if (dir > -1)
		{
			print_dirmsg(command);
			close(dir);
		}
	}
	else if (type == -3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (type == -4)
		print_dirmsg(command);
}

/*
prints the right error message for invalid command types
*/
static void	print_invalid_msg(t_cmds *cmd)
{
	if (cmd->id == 0 && cmd->fd_infile != -1)
	{
		if (is_dir(cmd->command[0]) > 0)
			print_error_msg(cmd->command[0], -4);
		else
			print_error_msg(cmd->command[0], -1);
	}
	else if (cmd->id > 0 && cmd->fd_infile < 0)
	{
		if (is_dir(cmd->command[0]) > 0)
			print_error_msg(cmd->command[0], -4);
		else
			print_error_msg(cmd->command[0], -1);
	}
}

/*
prints the appropriate error message for nonexistent/
nonexecutable commands
*/
void	nonexistent_cmd(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->valid == -1)
		{
			print_invalid_msg(cmd);
		}
		else if (cmd->valid == -2 && ft_strncmp(cmd->command[0], ".", 1) != 0)
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
				print_error_msg(cmd->command[0], -2);
			else if (cmd->id > 0 && cmd->fd_infile < 0)
				print_error_msg(cmd->command[0], -2);
		}
		else if (cmd->valid == -3)
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
				print_error_msg(cmd->command[0], -3);
			else if (cmd->id > 0 && cmd->fd_infile < 0)
				print_error_msg(cmd->command[0], -3);
		}
		cmd = cmd->next;
	}
}

/*
checks for incomplete . arguments
*/
void	dot_cmd(t_cmds **cmds)
{
	t_cmds	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->command[0])
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
			{
				print_usage_msg(cmd->command[0]);
			}
			else if (cmd->id > 0 && cmd->fd_infile < 0)
			{
				print_usage_msg(cmd->command[0]);
			}
		}
		cmd = cmd->next;
	}
}
