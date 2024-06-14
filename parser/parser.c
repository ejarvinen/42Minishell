/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/14 14:41:14 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;
	//t_toks	*node;
	
	//printf("Im in parser\n");
	tokens = checker(rl);
	if (!tokens)
		return (1);
	//printf("I made tokens\n");
	identifier(&tokens);
	//printf("I identified tokens\n");
	token_cleanup(&tokens, &shell->env);
	if (!tokens)
		return (1);
	//printf("I opened quotes and shit\n");
	/*node = tokens;
	while (node)
	{
		printf("token: %s\n", node->content);
		printf("file: %d\ncommand: %d\nargument: %d\npipe: %d\nin_redir: %d\nout_redir: %d\nappend: %d\nheredoc: %d\nheredoc_delim: %d\n", node->file, node->command, node->argument, node->pipe, node->in_redir, node->out_redir, node->append, node->heredoc, node->heredoc_delimiter);
		printf("---------------\n");
		node = node->next;
	}*/
	no_blanks_cleanup(&tokens);
	//printf("yolo\n");
	if (!tokens)
	{
		//printf("I exited after attempting blank space removal\n");
		return (1);
	}
	//printf("I removed blank space\n");
	shell->cmds = build_command_list(&tokens);
	ft_lstclear_toks(&tokens);
	if (!shell->cmds)
		return (1);
	//printf("I made a command list HELL YEAH\n");
	add_builtin_info(&shell->cmds);
	//printf("I added builtin info\n");
	add_cmds_info(&shell->cmds);
	//printf("I added commands info\n");
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