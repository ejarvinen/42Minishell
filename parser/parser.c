/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/16 10:30:12 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_invalid_cmd_info(t_cmds *cmd)
{
	cmd->builtin = 0;
	cmd->valid = -1;
}

static int	add_remaining_info(t_mini *shell)
{
	if (shell->cmds->command == NULL)
		fill_invalid_cmd_info(shell->cmds);
	else
		add_builtin_info(&shell->cmds);
	add_cmds_info(&shell->cmds);
	if (shell->cmds->command == NULL)
		return (0);
	return (validate_commands(&shell->cmds, &shell->env));
}

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
	no_blanks_cleanup(&tokens, shell);
	if (!tokens)
		return (1);
	expand_exit_code(&tokens, shell);
	if (!tokens)
		return (1);
	build_command_list(&tokens, shell);
	ft_lstclear_toks(&tokens);
	if (!shell->cmds)
		return (1);
	return (add_remaining_info(shell));
}
