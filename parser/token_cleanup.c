/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:51:53 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 13:38:18 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
removes single quotes in token
*/
static void	remove_singles(t_toks **token, int *index)
{
	t_toks	*item;
	char	*freeable;
	int		end_quote;

	item = *token;
	end_quote = *index + 1;
	while (item->content[end_quote] != 39 && item->content[end_quote] != '\0')
		end_quote++;
	freeable = item->content;
	item->content = (char *)malloc(sizeof(char) * (ft_strlen(freeable) - 1));
	if (!item->content)
	{
		parser_error("malloc fail");
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
removes double quotes in token
*/
static void	remove_doubles(t_mini *shell, t_toks **token, int *index)
{
	t_toks	*item;
	char	*freeable;
	int		end_quote;

	end_quote = end_quote_index(shell, token, index);
	item = *token;
	freeable = item->content;
	item->content = (char *)malloc(sizeof(char) * (ft_strlen(freeable) - 1));
	if (!item->content)
	{
		parser_error("malloc fail");
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
static int	remove_quotes(t_mini *shell, t_toks **token,
int *index, int quote_type)
{
	if (quote_type == 39)
	{
		remove_singles(token, index);
		if (*index < 0)
			return (1);
		return (0);
	}
	else if (quote_type == 34)
	{
		remove_doubles(shell, token, index);
		if (*index < 0)
			return (1);
		return (0);
	}
	return (1);
}

/*
looks for quotes and dollar signs in token
*/
static int	token_checker(t_mini *shell, t_toks **tokens)
{
	int		index;
	t_toks	*token;

	index = 0;
	token = *tokens;
	while (index < (int)ft_strlen(token->content))
	{
		if (token->content[index] == 36)
		{
			expand_dollar(shell, &token, &index, 0);
			if (index < 0)
				return (1);
		}
		else if (token->content[index] == 39 || token->content[index] == 34)
		{
			if (remove_quotes(shell, &token, &index, token->content[index]) > 1)
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
void	token_cleanup(t_mini *shell, t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		if (token_checker(shell, &token) > 0)
		{
			ft_lstclear_toks(tokens);
			return ;
		}
		token = token->next;
	}
}
