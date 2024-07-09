/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:13:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/09 11:38:13 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_cmd_info(t_cmds **cmds)
{
	t_cmds	*node;
	int		index;
	
	node = *cmds;
	while (node)
	{
		index = 1;
		printf("command id: %d\n", node->id);
		if (node->command == NULL)
			printf("command: NULL\n");
		else
			printf("command: %s\n", node->command[0]);
		printf("arguments: ");
		if ((node->command == NULL) || node->command[index] == NULL)
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
		index = 0;
		printf("outfile name(s): ");
		if ((node->outfile_name == NULL) || node->outfile_name[index] == NULL)
			printf("NULL\n");
		else
		{
			while (node->outfile_name[index])
			{
				printf("%s ", node->outfile_name[index]);
				index++;
			}
			printf("\n");
		}
		printf("infile fd: %d\n", node->fd_infile);
		printf("outfile fd: %d\n", node->fd_outfile[0]);
		printf("heredoc delimeter: %s\n", node->heredoc);
		printf("append: %d\n", node->append);
		printf("builtin: %d\n", node->builtin);
		printf("validity: %d\n", node->valid);
		printf("number of commands: %d\n", node->commands);
		printf("---------------\n");
		node = node->next;
	}
}
