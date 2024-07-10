/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:26:07 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 16:54:40 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds a new token to list of tokens
*/
static int	add_new_token(char *token, t_toks **tokens)
{
	t_toks	*new_token;

	new_token = ft_lstnew_toks(token);
	if (!new_token)
		return (1);
	initialize_token(new_token);
	ft_lstadd_back_toks(tokens, new_token);
	return (0);
}

/*
adds indexes to list of tokens
*/
void	add_indexes(t_toks **tokens)
{
	t_toks	*token;
	int		index;

	token = *tokens;
	index = 0;
	while (token)
	{
		token->id = index;
		index++;
		token = token->next;
	}
}

/*
frees all resources used for readline tokenizing
*/
static t_toks	*free_checker_resources(char *rl, t_toks **tokens)
{
	free(rl);
	if (tokens != NULL)
		ft_lstclear_toks(tokens);
	return (NULL);
}

/*
prints syntax error message when token contains uneven amount of
certain quote type
*/
static t_toks	*print_syntax_error_toks(char *rl,
t_toks **tokens, t_mini *shell)
{
	parser_error("syntax error");
	shell->syntax = 258;
	return (free_checker_resources(rl, tokens));
}

/*
tokenizes readline input, performs a quote check for each token and builds
returns a list of tokens if all tokens pass validity check; returns NULL for
any faulty token
*/
t_toks	*checker(char *input, t_mini *shell)
{
	char	*token;
	char	*rl;
	t_toks	*tokens;

	tokens = NULL;
	rl = ft_strdup(input);
	if (!rl)
		return (NULL);
	token = ft_strtok(rl);
	while (token)
	{
		if (quote_check(token) > 0)
		{
			if (add_new_token(token, &tokens) > 0)
				return (free_checker_resources(rl, &tokens));
		}
		else
			return (print_syntax_error_toks(rl, &tokens, shell));
		token = ft_strtok(NULL);
	}
	free(rl);
	add_indexes(&tokens);
	return (tokens);
}
