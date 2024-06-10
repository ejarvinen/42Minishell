/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/10 11:43:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;
	t_cmds	*node;
	int		index;
	
	tokens = checker(rl);
	if (!tokens)
		return (1);
	identifier(&tokens);
	token_touchup(&tokens, &shell->env);
	no_blanks_cleanup(&tokens);
	shell->cmds = build_command_list(&tokens);
	ft_lstclear_toks(&tokens, free);
	if (!shell->cmds)
		return (1);
	add_builtin_info(&shell->cmds);
	add_cmds_info(&shell->cmds);
	node = shell->cmds;
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
		printf("outfile name: %s\n", node->outfile_name);
		printf("heredoc delimeter: %s\n", node->heredoc);
		printf("builtin: %d\n", node->builtin);
		printf("number of commands: %d\n", node->commands);
		printf("---------------\n");
		node = node->next;
	}
	return (0);
}

	/*node = tokens;
	while (node)
	{
		printf("token: %s\n", node->content);
		printf("file: %d\ncommand: %d\nargument: %d\npipe: %d\nin_redir: %d\nout_redir: %d\nappend: %d\nheredoc: %d\nheredoc_delim: %d\n", node->file, node->command, node->argument, node->pipe, node->in_redir, node->out_redir, node->append, node->heredoc, node->heredoc_delimiter);
		printf("---------------\n");
		node = node->next;
	}*/