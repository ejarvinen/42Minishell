/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:13:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/12 13:17:23 by emansoor         ###   ########.fr       */
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
		printf("infile name: %s\n", node->infile_name);
		printf("infile fd: %d\n", node->fd_infile);
		printf("outfile name: %s\n", node->outfile_name);
		printf("outfile fd: %d\n", node->fd_outfile);
		printf("heredoc delimeter: %s\n", node->heredoc);
		printf("builtin: %d\n", node->builtin);
		printf("number of commands: %d\n", node->commands);
		printf("---------------\n");
		node = node->next;
	}
}
