/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/17 08:39:52 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;
	
	tokens = checker(rl);
	if (!tokens)
		return (1);
	identifier(&tokens);
	token_cleanup(&tokens, &shell->env);
	if (!tokens)
		return (1);
	no_blanks_cleanup(&tokens);
	if (!tokens)
		return (1);
	shell->cmds = build_command_list(&tokens);
	ft_lstclear_toks(&tokens);
	if (!shell->cmds)
		return (1);
	add_builtin_info(&shell->cmds);
	add_cmds_info(&shell->cmds);
	validate_commands(&shell->cmds, &shell->env);
	if (!shell->cmds)
		return (1);
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