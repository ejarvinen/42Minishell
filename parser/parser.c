/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:18:27 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/20 15:10:29 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_empty(t_toks **tokens)
{
	t_toks	*prev;
	t_toks	*next;
	t_toks	*node;

	prev = *tokens;
	while (prev && prev->content[0] == '\0')
	{
		*tokens = prev->next;
		free(prev->content);
		free(prev);
		prev = *tokens;
	}
	while (prev)
	{
		if (prev->next && prev->next->content[0] == '\0')
		{
			node = prev->next;
			next = node->next;
			prev->next = next;
			free(node->content);
			free(node);
		}
		else
			prev = prev->next;
	}
}

static void	trim_token(t_toks **token)
{
	t_toks	*temp;
	char	*new;

	temp = *token;
	while (temp != NULL)
	{
		new = temp->content;
		temp->content = ft_strtrim(new, " \t");
		if (!temp->content)
		{
			ft_lstclear_toks(token);
			return ;
		}
		free(new);
		temp = temp->next;
	}
	remove_empty(token);
}

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

int	parser(char *rl, t_mini *shell)
{
	t_toks	*tokens;

	tokens = checker(rl, shell);
	if (!tokens)
		return (1);
	trim_token(&tokens);
	if (!tokens)
		return (1);
	add_indexes(&tokens);
	identifier(&tokens);
	token_cleanup(shell, &tokens);
	if (!tokens)
		return (1);
	if (ft_lstsize_toks(tokens) == 1 && ft_strcmp(tokens->content, "\0") == 0)
	{
		ft_lstclear_toks(&tokens);
		return (0);
	}
	no_blanks_cleanup(&tokens, shell);
	if (!tokens)
		return (1);
	expand_exit_code(&tokens, shell);
	if (!tokens)
		return (1);
	return (add_remaining_info(shell, tokens));
}
