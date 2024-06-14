/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:51:53 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/14 16:34:00 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
copies string from to string to while skipping given indexes
*/
static void	strcpy_without_quotes(char *to, char *from, int fstquote, int sqnquote)
{
	int	index;
	int	skip_index;

	index = 0;
	skip_index = 0;
	while (from[skip_index] != '\0')
	{
		if (skip_index == fstquote)
			skip_index++;
		else if (skip_index == sqnquote)
			skip_index++;
		else
		{
			to[index] = from[skip_index];
			index++;
			skip_index++;
		}
	}
	to[index] = '\0';
}

/*
removes single quotes in token
*/
static void	remove_singles(t_toks **token, int *index)
{
	t_toks	*item;
	char	*freeable;
	int	end_quote;

	item = *token;
	end_quote = *index + 1;
	while (item->content[end_quote] != 39 && item->content[end_quote] != '\0')
		end_quote++;
	freeable = item->content;
	item->content = (char *)malloc(sizeof(char) * (ft_strlen(freeable) - 1));
	if (!item->content)
	{
		*index = -1;
		return ;
	}
	strcpy_without_quotes(item->content, freeable, *index, end_quote);
	free(freeable);
	*index = end_quote - 2;
	if (*index < 0)
		*index = 0;
}

/*
returns index for the matching double quote, expands dollar signs where possible
*/
static int	end_quote_index(t_toks **token, t_env **envs, int *index)
{
	t_toks	*item;
	int	end_quote;
	
	item = *token;
	end_quote = *index + 1;
	while (item->content[end_quote] != 34 && item->content[end_quote] != '\0')
	{
		if (item->content[end_quote] == 36)
		{
			expand_dollar(token, envs, &end_quote, 1);
			if (end_quote < 0)
				return (-1);
			item = *token;
		}
		else
			end_quote++;
	}
	return (end_quote);
}

/*
removes double quotes in token
*/
static void	remove_doubles(t_toks **token, t_env **envs, int *index)
{
	t_toks	*item;
	char	*freeable;
	int	end_quote;

	end_quote = end_quote_index(token, envs, index);
	item = *token;
	freeable = item->content;
	item->content = (char *)malloc(sizeof(char) * (ft_strlen(freeable) - 1));
	if (!item->content)
	{
		*index = -1;
		return ;
	}
	strcpy_without_quotes(item->content, freeable, *index, end_quote);
	free(freeable);
	*index = end_quote - 2;
	if (*index < 0)
		*index = 0;
}

/*
checks for a quote type and removes them accordingly
*/
static int	remove_quotes(t_toks **token, t_env **envs, int *index, int quote_type)
{
	if (quote_type == 39)
	{
		remove_singles(token, index);
		if (index < 0)
			return (1);
		return (0);
	}
	else if (quote_type == 34)
	{
		remove_doubles(token, envs, index);
		if (index < 0)
			return (1);
		return (0);
	}
	return (1);
}

/*
looks for quotes and dollar signs in token
*/
static int	token_checker(t_toks **tokens, t_env **envs)
{
	int	index;
	t_toks	*token;

	index = 0;
	token = *tokens;
	while (index < (int)ft_strlen(token->content))
	{
		if (token->content[index] == 36)
		{
			expand_dollar(&token, envs, &index, 0);
			if (index < 0)
				return (1);
		}
		else if (token->content[index] == 39 || token->content[index] == 34)
		{
			if (remove_quotes(&token, envs, &index, token->content[index]) > 1)
				return (1);
			index++;
		}
		else
			index++;
	}
	return (0);
}

/*
gets rid of quotes and expands dollar signs where possible
*/
void	token_cleanup(t_toks **tokens, t_env **envs)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		if (token_checker(&token, envs) > 0)
		{
			ft_lstclear_toks(tokens);
			return ;
		}
		token = token->next;
	}
}
