/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:56:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 10:38:10 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
returns syntax error message
*/
int	syntax_check(t_toks *token, t_cmds **cmds, t_mini *shell)
{
	if (token == NULL)
	{
		parser_error("syntax error near unexpected token");
		shell->syntax = 1;
		if (cmds)
		{
			clear_temp(cmds);
			ft_lstclear_pars(cmds);
		}
		return (1);
	}
	return (0);
}

/*
checks if token or command list has ended prematurely and prints
the appropriate error message accordingly
*/
int	syntax_checker(t_cmds **cmds, t_cmds *cmd, t_toks *token, t_mini *shell)
{
	if (token == NULL)
	{
		parser_error("syntax error");
		shell->syntax = 1;
		clear_temp(cmds);
		ft_lstclear_pars(cmds);
		return (1);
	}
	else if (cmd == NULL && token != NULL)
	{
		syntax_check(NULL, cmds, shell);
		return (1);
	}
	else if (cmd == NULL)
		return (1);
	cmd->append = 0;
	return (0);
}

int	is_delimiter(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, "<<") == 0)
		return (1);
	else if (ft_strcmp(str, ">>") == 0)
		return (1);
	else if (ft_strcmp(str, "<") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (1);
	return (0);
}

static int	check_for_repeat_delims(t_mini *shell, t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;

	token = *tokens;
	next = token->next;
	while (next)
	{
		if (ft_strcmp(token->content, next->content) == 0
			&& is_delimiter(token->content) > 0)
			return (syntax_check(NULL, NULL, shell));
		token = token->next;
		next = next->next;
	}
	return (0);
}

int	syntax_scan(t_mini *shell, t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	if (ft_strcmp(token->content, "|") == 0)
	{
		ft_lstclear_toks(tokens);
		return (syntax_check(NULL, NULL, shell));
	}
	else if (ft_lstsize_toks(token) == 1 && is_delimiter(token->content) > 0)
	{
		ft_lstclear_toks(tokens);
		return (syntax_check(NULL, NULL, shell));
	}
	if (check_for_repeat_delims(shell, tokens) > 0)
	{
		ft_lstclear_toks(tokens);
		return (1);
	}
	return (0);
}
