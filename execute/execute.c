/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:34:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 08:42:32 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	safe_to_run(t_cmds *cmds)
{
	if (cmds->command == NULL
		|| ((cmds->fd_infile == -1 || cmds->valid < 0)
			&& cmds->heredoc == NULL) || cmds->fd_outfile[0] < 0)
		return (0);
	return (1);
}

/*
if the command to be executed is not the first or the last command
in a pipeline, sets up pipes according to even and odd numbered ids
*/
static void	set_pipes(t_mini *shell, t_cmds *cmd)
{
	t_cmds	*next;
	t_cmds	*prev;

	prev = shell->cmds;
	while (prev->id != cmd->id)
	{
		if (prev->fd_infile != 0)
			close(prev->fd_infile);
		if (prev->fd_outfile[0] != 1)
			close(prev->fd_outfile[0]);
		prev = prev->next;
	}
	next = cmd->next;
	while (next)
	{
		if (next->fd_infile != 0)
			close(next->fd_infile);
		if (next->fd_outfile[0] != 1)
			close(next->fd_outfile[0]);
		next = next->next;
	}
	if (dup2(cmd->fd_infile, STDIN_FILENO) < 0)
	{
		perror("minishell5");
		panic(shell, 9);
	}
	close(cmd->fd_infile);
	if (dup2(cmd->fd_outfile[0], STDOUT_FILENO) < 0)
	{
		perror("minishell6");
		panic(shell, 9);
	}
	close(cmd->fd_outfile[0]);
}

/*
sets up pipes and redirections according to command type and runs
a builtin or execve accordingly
*/
void	execute(t_mini *shell, t_cmds *cmd)
{
	if (cmd->id == 0)
		first_command(shell, cmd);
	else if (cmd->id == cmd->commands - 1)
		last_command(shell, cmd);
	else
		set_pipes(shell, cmd);
	if (cmd->builtin == 1)
	{
		ft_freearray(shell->env_p);
		check_builtin(shell, cmd);
	}
	else
	{
		if (execve(cmd->path, cmd->command, shell->env_p) == -1)
			panic(shell, 126);
	}
}
