/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:20:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 10:17:55 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
if token contains more than just heredoc delimiter, updates token
info accordingly
*/
static void	heredoc_long_str(t_toks *token, t_toks *next)
{
	if (ft_strncmp(token->content, "<<", 2) == 0)
	{
		token->heredoc = 1;
		if (next)
			next->heredoc = 0;
	}
	else if (ft_strncmp((token->content
				+ (int)ft_strlen(token->content) - 2), "<<", 2) == 0)
	{
		if (next)
			next->heredoc = 1;
		token->heredoc = 0;
	}
	else
	{
		token->heredoc = 1;
		token->command = 1;
	}
}

/*
checks for heredoc delimiter in a token
*/
static void	check_heredoc(t_toks *token, t_toks *next)
{
	if (token->heredoc_delimiter > 0 && ft_strlen(token->content) == 2)
	{
		token->heredoc = 0;
		if (next)
			next->heredoc = 1;
	}
	else if (token->heredoc_delimiter > 0 && ft_strlen(token->content) > 2)
	{
		heredoc_long_str(token, next);
	}
	else
	{
		token->heredoc = 0;
		if (next)
			next->heredoc = 0;
	}
}

/*
identifies heredoc in a list of tokens
*/
void	identify_heredoc(t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;

	token = *tokens;
	if (ft_lstsize_toks(token) > 1)
	{
		next = token->next;
		while (next)
		{
			if (token->heredoc < 1)
				check_heredoc(token, next);
			token = token->next;
			next = next->next;
		}
	}
	if (token->heredoc < 1)
		check_heredoc(token, NULL);
}

/*
checks for tokens containing only a single delimiter and updates token
info accordingly
*/
static void	double_check(t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	if (ft_lstsize_toks(token) == 1)
		return ;
	while (token)
	{
		if (struct_sum(token) != 1)
		{
			if (ft_strcmp(token->content, "|") == 0)
				add_pipe_info(token);
			else if (ft_strcmp(token->content, "<") == 0)
				add_inredir_info(token);
			else if (ft_strcmp(token->content, ">") == 0)
				add_outredir_info(token);
			else if (ft_strcmp(token->content, ">>") == 0)
				add_append_info(token);
			else if (ft_strcmp(token->content, "<<") == 0)
				add_hredir_info(token);
		}
		token = token->next;
	}
}

/*
goes through a list of tokens and identifies each token by it's contents
*/
void	identifier(t_toks **tokens)
{
	identify_delims(tokens);
	identify_heredoc(tokens);
	recognize_file(tokens);
	identify_commands(tokens);
	identify_args(tokens);
	double_check(tokens);
}
