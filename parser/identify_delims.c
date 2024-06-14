/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_delims.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 06:38:09 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/14 16:13:20 by emansoor         ###   ########.fr       */
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
sets everything else in token to zero except for pipe
*/
static void	sure_pipe(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->append = 0;
}

/*
counts how many pipe | symbols can be found in token
*/
static int	pipe_found(t_toks *token)
{
	size_t	index;
	int	pipes;
	
	if (ft_strncmp(token->content, "|", 1) == 0 && ft_strlen(token->content) == 1)
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
sets everything else to zero in token except for in_redir flag
*/
static void	sure_inredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->out_redir = 0;
	token->append = 0;
	token->pipe = 0;
}

/*
sets everything else to zero in token except for out_redir flag
*/
static void	sure_outredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->append = 0;
	token->pipe = 0;
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
returns the number of type of redirector in token when token contains several delimiters
*/
static int	search_mixedflag_token(char *token, int type, int doubles)
{
	int	redirs;
	size_t	index;

	redirs = 0;
	index = 0;
	if (doubles > 0)
	{
		while (index < ft_strlen(token) - 2)
		{
			redirs += find_doubredir(token, &index, type);
			index++;
		}
	}
	else
	{
		while (index < ft_strlen(token))
		{
			redirs += find_redir(token, &index, type);
			index++;
		}
	}
	return (redirs);
}

/*
counts how many times < or > is found in token
*/
static int	redir_found(t_toks *token, int type)
{
	if (type == '<')
	{
		if (ft_strncmp(token->content, "<", 1) == 0 && ft_strlen(token->content) == 1)
		{
			sure_inredir(token);
			return (1);
		}
	}
	else if (type == '>')
	{
		if (ft_strncmp(token->content, ">", 1) == 0 && ft_strlen(token->content) == 1)
		{
			sure_outredir(token);
			return (1);
		}
	}
	return (search_mixedflag_token(token->content, type, 0));
}

/*
sets everything to zero in token except for append flag
*/
static void	sure_append(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->pipe = 0;
}

/*
sets everything to zero in token except for heredoc_delim flag
*/
static void	sure_hredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->pipe = 0;
	token->append = 0;
}

/*
counts how many << and >> operators can be found in a token
*/
static int	doubredir_found(t_toks *token, int type)
{
	if (type == '>')
	{
		if (ft_strncmp(token->content, ">>", 2) == 0 && ft_strlen(token->content) == 2)
		{
			sure_append(token);
			return (1);
		}
	}
	else if (type == '<')
	{
		if (ft_strncmp(token->content, "<<", 2) == 0 && ft_strlen(token->content) == 2)
		{
			sure_hredir(token);
			return (1);
		}
	}
	return (search_mixedflag_token(token->content, type, 1));
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
