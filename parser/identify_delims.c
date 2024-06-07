/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_delims.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 06:38:09 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/06 14:16:16 by emansoor         ###   ########.fr       */
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
static int	pipe_found(char *token)
{
	size_t	index;
	int	pipes;
	
	if (ft_strncmp(token, "|", 1) == 0 && ft_strlen(token) == 1)
		return (1);
	index = 0;
	pipes = 0;
	while (index < ft_strlen(token))
	{
		if (token[index] == '|')
		{
			if (in_quotes(token, index) == 0)
				pipes++;
		}
		index++;
	}
	return (pipes);
}

/*
helper function to determine whether < or > to be found can be added to the total
*/
static int	find_redir(char *token, size_t *index, int type)
{
	if (token[*index] == type)
	{
		if (in_quotes(token, *index) > 0)
			return (0);
		else if ((*index > 0 && token[*index - 1] == type) || (*index < ft_strlen(token) - 1 && token[*index + 1] == type))
			return (0);
		return (1);
	}
	return (0);
}

/*
counts how many times < or > is found in token
*/
static int	redir_found(char *token, int type)
{
	size_t	index;
	int	redirs;

	if (type == '<')
	{
		if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1)
			return (1);
	}
	else if (type == '>')
	{
		if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1)
			return (1);
	}
	index = 0;
	redirs = 0;
	while (index < ft_strlen(token))
	{
		redirs += find_redir(token, &index, type);
		index++;
	}
	return (redirs);
}

/*
helper function to find out how many times << or >> exists in token
*/
static int	find_doubredir(char *token, size_t *index, int type)
{
	if (type == '>' && ft_strncmp((token + *index), ">>", 2) == 0)
	{
		if (in_quotes(token, *index) > 0)
			return (0);
		else if ((*index > 0 && token[*index - 1] == type) || (*index < ft_strlen(token) - 1 && token[*index + 2] == type))
			return (0);
		return (1);
	}
	else if (type == '<' && ft_strncmp((token + *index), "<<", 2) == 0)
	{
		if (in_quotes(token, *index) > 0)
			return (0);
		else if ((*index > 0 && token[*index - 1] == type) || (*index < ft_strlen(token) - 1 && token[*index + 2] == type))
			return (0);
		return (1);
	}
	return (0);
}

/*
counts how many << and >> operators can be found in a token
*/
static int	doubredir_found(char *token, int type)
{
	size_t	index;
	int	doubles;

	if (type == '>')
	{
		if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2)
			return (1);
	}
	else if (type == '<')
	{
		if (ft_strncmp(token, "<<", 2) == 0 && ft_strlen(token) == 2)
			return (1);
	}
	index = 0;
	doubles = 0;
	while (index < ft_strlen(token) - 2)
	{
		doubles += find_doubredir(token, &index, type);
		index++;
	}
	return (doubles);
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
		token->pipe = pipe_found(token->content);
		token->in_redir = redir_found(token->content, '<');
		token->out_redir = redir_found(token->content, '>');
		if (ft_strlen(token->content) > 1)
		{
			token->append = doubredir_found(token->content, '>');
			token->heredoc_delimiter = doubredir_found(token->content, '<');
		}
		else
		{
			token->append = 0;
			token->heredoc_delimiter = 0;
		}
		token = token->next;
	}
}
