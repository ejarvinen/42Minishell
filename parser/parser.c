/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 09:10:55 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_invalid_cmd_info(t_cmds *cmds)
{
	t_cmds	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->command == NULL)
		{
			cmd->builtin = 0;
			cmd->valid = -1;
		}
		cmd = cmd->next;
	}
}

static int	add_remaining_info(t_mini *shell, t_toks *tokens)
{
	t_cmds	*cmd;

	build_command_list(&tokens, shell);
	ft_lstclear_toks(&tokens);
	if (!shell->cmds)
		return (1);
	fill_invalid_cmd_info(shell->cmds);
	add_builtin_info(&shell->cmds);
	add_cmds_info(&shell->cmds);
	cmd = shell->cmds;
	while (cmd)
	{
		if (cmd->command != NULL)
		{
			validate_commands(shell, cmd);
			if (!shell->cmds)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	token_cleanup_check(t_mini *shell, t_toks *tokens)
{
	int	flag;

	flag = ft_strncmp(tokens->content, "$'", 2);
	token_cleanup(shell, &tokens);
	if (!tokens)
		return (1);
	if (ft_lstsize_toks(tokens) == 1 && ft_strcmp(tokens->content, "\0") == 0)
	{
		if (flag == 0)
			return (2);
		ft_lstclear_toks(&tokens);
		return (0);
	}
	return (2);
}

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;
	int		checkup;

	tokens = checker(rl, shell);
	if (!tokens)
		return (1);
	trim_token(&tokens);
	if (!tokens)
		return (1);
	if (syntax_scan(shell, &tokens) > 0)
		return (1);
	add_indexes(&tokens);
	identifier(&tokens);
	checkup = token_cleanup_check(shell, tokens);
	if (checkup < 2)
		return (checkup);
	no_blanks_cleanup(&tokens, shell);
	if (!tokens)
		return (1);
	if (syntax_scan(shell, &tokens) > 0)
		return (1);
	expand_exit_code(&tokens, shell);
	if (!tokens)
		return (1);
	return (add_remaining_info(shell, tokens));
}
