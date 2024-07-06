/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_delims_redirs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:25:41 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 14:29:51 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
helper function to determine whether < or > to be found can be added to the total
*/
static int	find_redir(char *token, size_t *index, int type)
{
	if (token[*index] == type)
	{
		if (in_quotes(token, *index) > 0)
			return (0);
		else if ((*index > 0 && token[*index - 1] == type)
			|| (*index < ft_strlen(token) - 1 && token[*index + 1] == type))
			return (0);
		return (1);
	}
	return (0);
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
		else if ((*index > 0 && token[*index - 1] == type)
			|| (*index < ft_strlen(token) - 1 && token[*index + 2] == type))
			return (0);
		return (1);
	}
	else if (type == '<' && ft_strncmp((token + *index), "<<", 2) == 0)
	{
		if (in_quotes(token, *index) > 0)
			return (0);
		else if ((*index > 0 && token[*index - 1] == type)
			|| (*index < ft_strlen(token) - 1 && token[*index + 2] == type))
			return (0);
		return (1);
	}
	return (0);
}

/*
returns the number of type of redirector in token when token contains
several delimiters
*/
static int	search_mixedflag_token(char *token, int type, int doubles)
{
	int		redirs;
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
int	redir_found(t_toks *token, int type)
{
	if (type == '<')
	{
		if (ft_strcmp(token->content, "<") == 0)
		{
			sure_inredir(token);
			return (1);
		}
	}
	else if (type == '>')
	{
		if (ft_strcmp(token->content, ">") == 0)
		{
			sure_outredir(token);
			return (1);
		}
	}
	return (search_mixedflag_token(token->content, type, 0));
}

/*
counts how many << and >> operators can be found in a token
*/
int	doubredir_found(t_toks *token, int type)
{
	if (type == '>')
	{
		if (ft_strcmp(token->content, ">>") == 0)
		{
			sure_append(token);
			return (1);
		}
	}
	else if (type == '<')
	{
		if (ft_strcmp(token->content, "<<") == 0)
		{
			sure_hredir(token);
			return (1);
		}
	}
	return (search_mixedflag_token(token->content, type, 1));
}
