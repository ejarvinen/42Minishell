/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_delim_args_and_cmds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:41:15 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 10:18:32 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
checks if token list contains previous commands before given index in
the same list
*/
static int	check_for_previous_cmds(t_toks **tokens, int index)
{
	int		cmds;
	t_toks	*token;

	token = *tokens;
	cmds = 0;
	while (token->id != index - 1)
	{
		if (token->pipe > 0)
			cmds = 0;
		else if (token->command > 0)
			cmds++;
		token = token->next;
	}
	return (cmds);
}

/*
checks for command indicators and updates token info accordingly
*/
static void	check_for_cmd_indicators(t_toks **tokens,
t_toks *token, t_toks *next)
{
	if (token->pipe > 0 && ft_strlen(token->content) == 1)
	{
		token->command = 0;
		if (next)
			next->command = 1;
	}
	else if (token->pipe > 0 && ft_strlen(token->content) > 1)
	{
		token->command = 1;
		if (next)
			next->command = 0;
	}
	else if (next && check_for_previous_cmds(tokens, next->id) == 0
		&& token->append < 1 && token->in_redir < 1 && token->out_redir < 1
		&& token->heredoc_delimiter < 1 && token->file < 1
		&& token->heredoc < 1)
	{
		token->command = 1;
		next->command = 0;
	}
	else
		token->command = 0;
}

/*
identifies commands in a list of tokens
*/
void	identify_commands(t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;

	token = *tokens;
	if (ft_lstsize_toks(token) == 1)
	{
		token->command = 1;
		return ;
	}
	next = token->next;
	while (next)
	{
		if (token->command < 1)
			check_for_cmd_indicators(tokens, token, next);
		token = token->next;
		next = next->next;
	}
	if (token->command < 1)
		check_for_cmd_indicators(tokens, token, NULL);
}

/*
marks all tokens not already identified as arguments
*/
void	identify_args(t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		if (token->argument < 0)
		{
			if (token->id != 0 && token->append < 1 && token->file < 1
				&& token->heredoc < 1 && token->heredoc_delimiter < 1
				&& token->in_redir < 1 && token->out_redir < 1
				&& token->command < 1 && token->pipe < 1)
				token->argument = 1;
			else
				token->argument = 0;
		}
		token = token->next;
	}
}
