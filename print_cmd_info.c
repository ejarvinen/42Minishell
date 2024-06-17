/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:13:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/17 08:21:47 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_info(t_cmds **cmds)
{
	t_cmds	*node;
	int		index;
	
	node = *cmds;
	while (node)
	{
		index = 1;
		printf("command id: %d\n", node->id);
		printf("command: %s\n", node->command[0]);
		printf("arguments: ");
		if (node->command[index] == NULL)
			printf("NULL\n");
		else
		{
			while (node->command[index])
			{
				printf("%s ", node->command[index]);
				index++;
			}
			printf("\n");
		}
		if (node->builtin != 1)
		{
			if (node->valid == -1 || node->valid == -3)
				printf("path: no valid path exists\n");
			else
				printf("path: %s\n", node->path);
		}
		else
			printf("path: NULL (builtin)\n");
		printf("infile name: %s\n", node->infile_name);
		printf("infile fd: %d\n", node->fd_infile);
		printf("outfile name: %s\n", node->outfile_name);
		printf("outfile fd: %d\n", node->fd_outfile);
		printf("heredoc delimeter: %s\n", node->heredoc);
		printf("append: %d\n", node->append);
		printf("builtin: %d\n", node->builtin);
		printf("validity: %d\n", node->valid);
		printf("number of commands: %d\n", node->commands);
		printf("---------------\n");
		node = node->next;
	}
}
