/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 07:49:29 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/17 08:46:26 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
prints bash like error message for incomplete . arguments
*/
static void	print_usage_msg(char *command, t_mini *shell)
{
	if (ft_strcmp(command, ".") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": usage: . filename [arguments]\n", 2);
		exit_code(shell, 2, 0);
	}
	else if (ft_strcmp(command, "\0") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_code(shell, 127, 0);
	}
}

/*
prints error messages by command type
*/
static void	print_error_msg(char *command, int type, t_mini *shell)
{
	int	dir;

	if (type == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit_code(shell, 127, 0);
	}
	else if (type == -2 || type == -4)
	{
		dir = open(command, O_DIRECTORY);
		if (dir > -1)
		{
			print_dirmsg(command, shell);
			close(dir);
		}
	}
	else if (type == -3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit_code(shell, 126, 0);
	}
}

/* 	else if (type == -4)
		print_dirmsg(command, shell); */

/*
prints the right error message for invalid command types
*/
static void	print_invalid_msg(t_cmds *cmd, t_mini *shell)
{
	if (cmd->id == 0 && cmd->fd_infile != -1)
	{
		if (is_dir(cmd->command[0]) > 0)
			print_error_msg(cmd->command[0], -4, shell);
		else
			print_error_msg(cmd->command[0], -1, shell);
	}
	else if (cmd->id > 0 && cmd->fd_infile < 0)
	{
		if (is_dir(cmd->command[0]) > 0)
			print_error_msg(cmd->command[0], -4, shell);
		else
			print_error_msg(cmd->command[0], -1, shell);
	}
}

/*
prints the appropriate error message for nonexistent/
nonexecutable commands
*/
void	nonexistent_cmd(t_mini *shell)
{
	t_cmds	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->valid == -1)
		{
			print_invalid_msg(cmd, shell);
		}
		else if (cmd->valid == -2 && ft_strncmp(cmd->command[0], ".", 1) != 0)
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
				print_error_msg(cmd->command[0], -2, shell);
			else if (cmd->id > 0 && cmd->fd_infile < 0)
				print_error_msg(cmd->command[0], -2, shell);
		}
		else if (cmd->valid == -3)
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
				print_error_msg(cmd->command[0], -3, shell);
			else if (cmd->id > 0 && cmd->fd_infile < 0)
				print_error_msg(cmd->command[0], -3, shell);
		}
		cmd = cmd->next;
	}
}

/*
checks for incomplete . arguments
*/
void	dot_cmd(t_mini *shell)
{
	t_cmds	*cmd;

	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->command[0] != NULL && ft_strcmp(cmd->command[0], "\0") != 0)
		{
			if (cmd->id == 0 && cmd->fd_infile != -1)
			{
				print_usage_msg(cmd->command[0], shell);
			}
			else if (cmd->id > 0 && cmd->fd_infile < 0)
			{
				print_usage_msg(cmd->command[0], shell);
			}
		}
		cmd = cmd->next;
	}
}
