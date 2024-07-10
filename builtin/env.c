/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:49:54 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 08:24:08 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	ft_env(t_mini *shell, t_cmds *cmd)
{
	t_env	*temp;
	
	temp = shell->env;
	while(temp)
	{
		if (temp->equal == 1)
		{
			/*if (cmd->fd_outfile[0] > 1)
				print_to_file(temp, cmd);
			else
				print_to_terminal(temp, cmd);*/
			ft_putstr_fd(temp->key, cmd->fd_outfile[0]);
			ft_putstr_fd("=", cmd->fd_outfile[0]);
			if (temp->value != NULL)
				ft_putstr_fd(temp->value, cmd->fd_outfile[0]);
			ft_putchar_fd('\n', cmd->fd_outfile[0]);
		}
		temp = temp->next;
	}
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
	return (0);
}

/*
static void	print_to_file(t_env *temp, t_cmds *cmd)
{
		ft_putstr_fd(temp->key, cmd->fd_outfile[0]);
		ft_putstr_fd("=", cmd->fd_outfile[0]);
		if (temp->value != NULL)
			ft_putstr_fd(temp->value, cmd->fd_outfile[0]);
		ft_putchar_fd('\n', cmd->fd_outfile[0]);
}

int	ft_env(t_mini *shell, t_cmds *cmd)
{
	t_env	*temp;
	
	temp = shell->env;
	while(temp)
	{
		if (temp->equal == 1)
		{
			if (cmd->fd_outfile[0] > 1)
				print_to_file(temp, cmd);
			else
				print_to_terminal(temp);
		}
		temp = temp->next;
	}
	if (cmd->c_pid != -1)
	{
		free_data(shell, NULL);
		exit(0);
	}
	return (0);
}*/
