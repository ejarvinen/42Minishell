/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 07:51:52 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 07:52:12 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds the reading and writing ends of a pipe to array of pipe filedescriptors
*/
static void	add_pipefds(int *pipefds, int *index, int rd_end, int w_end)
{
	pipefds[*index] = rd_end;
	(*index)++;
	pipefds[*index] = w_end;
	(*index)++;
}

/*
mallocs an array of ints for a set of two pipes; if pipeline has only
two commands, the second pipeline is not opened, but marked as -1
*/
int	*setup_pipes(t_cmds *cmds)
{
	int	*pipefds;
	int	fds[2];
	int	index;

	pipefds = (int *)malloc(sizeof(int) * 4);
	if (!pipefds)
	{
		perror("minishell");
		return (NULL);
	}
	index = 0;
	while (index < 4)
	{
		if (pipe(fds) < 0)
		{
			perror("minishell");
			free(pipefds);
			return (NULL);
		}
		if (index > 1 && cmds->commands == 2)
			add_pipefds(pipefds, &index, -1, -1);
		else
			add_pipefds(pipefds, &index, fds[READ_END], fds[WRITE_END]);
	}
	return (pipefds);
}
