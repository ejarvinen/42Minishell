/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_delims.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 06:38:09 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 10:21:59 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
looks for the first single or double quote in str and returns is, returns
zero if neither quote type is found
*/
static int	quote_identifier(char const *str)
{
	int	index;
	int	quote;

	index = 0;
	quote = 0;
	while (str[index])
	{
		if (str[index] == 39 || str[index] == 34)
		{
			if (str[index] == 39)
				quote = 39;
			else
				quote = 34;
			break ;
		}
		index++;
	}
	return (quote);
}

/*
counts the quote type found in token between indexes index and end
*/
static int	quote_count(char *token, size_t index, size_t end, int quote_type)
{
	int	quotes;

	quotes = 0;
	if (end < index)
	{
		while (index > end - 1)
		{
			if (token[index] == quote_type)
				quotes++;
			index--;
		}
	}
	else
	{
		while (index < end)
		{
			if (token[index] == quote_type)
				quotes++;
			index++;
		}
	}
	return (quotes);
}

/*
checks if token contains quotes and then calculates how many times that type
of quote can be found before and after a given index; if either number is odd,
it returns 1, returns zero when current index is not inside quotes
*/
int	in_quotes(char *token, size_t index)
{
	int	quote_type;
	int	quotes_before;
	int	quotes_after;

	quote_type = quote_identifier(token);
	if (quote_type == 0)
		return (0);
	quotes_before = quote_count(token, index, 0, quote_type);
	quotes_after = quote_count(token, index, ft_strlen(token), quote_type);
	if (quotes_before % 2 != 0 || quotes_after % 2 != 0)
		return (1);
	return (0);
}

/*
counts how many pipe | symbols can be found in token
*/
static int	pipe_found(t_toks *token)
{
	size_t	index;
	int		pipes;

	if (ft_strcmp(token->content, "|") == 0)
	{
		sure_pipe(token);
		return (1);
	}
	index = 0;
	pipes = 0;
	while (index < ft_strlen(token->content))
	{
		if (token->content[index] == '|')
		{
			if (in_quotes(token->content, index) == 0)
				pipes++;
		}
		index++;
	}
	return (pipes);
}

/*
counts and adds all the delimiter info to each token
*/
void	identify_delims(t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		token->pipe = pipe_found(token);
		token->in_redir = redir_found(token, '<');
		token->out_redir = redir_found(token, '>');
		if (ft_strlen(token->content) > 1)
		{
			token->append = doubredir_found(token, '>');
			token->heredoc_delimiter = doubredir_found(token, '<');
		}
		else
		{
			token->append = 0;
			token->heredoc_delimiter = 0;
		}
		token = token->next;
	}
}
