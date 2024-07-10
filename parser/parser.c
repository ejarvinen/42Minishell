/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 16:14:07 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;

	tokens = checker(rl, shell);
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
	if (shell->cmds->command == NULL)
	{
		shell->cmds->builtin = 0;
		shell->cmds->valid = -1;
	}
	else
		add_builtin_info(&shell->cmds);
	add_cmds_info(&shell->cmds);
	if (shell->cmds->command == NULL)
		return (0);
	return (validate_commands(&shell->cmds, &shell->env));
}
