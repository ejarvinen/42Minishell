/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 16:47:54 by emansoor         ###   ########.fr       */
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
	return (validate_commands(&shell->cmds, &shell->env));
}
