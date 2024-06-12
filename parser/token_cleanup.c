/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:51:53 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/12 14:39:49 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	strcpy_singles(char *to, char *from, int fstquote, int sqnquote)
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
	strcpy_singles(item->content, freeable, *index, end_quote);
	free(freeable);
	*index = end_quote - 2;
}

static void	remove_doubles(t_toks **token, t_env **envs, int *index)
{
	t_toks	*item;
	char	*freeable;
	int	end_quote;

	item = *token;
	end_quote = *index + 1;
	while (item->content[end_quote] != 34 && item->content[end_quote] != '\0')
	{
		if (item->content[end_quote] == 36)
		{
			expand_dollar(token, envs, &end_quote, 1);
			item = *token;
		}
		end_quote++;
	}
	freeable = item->content;
	item->content = (char *)malloc(sizeof(char) * (ft_strlen(freeable) - 1));
	if (!item->content)
	{
		*index = -1;
		return ;
	}
	strcpy_singles(item->content, freeable, *index, end_quote);
	*index = end_quote - 2;
	free(freeable);
}

static int	token_fucker(t_toks **item, t_env **envs)
{
	int	index;
	t_toks	*token;

	index = 0;
	token = *item;
	while (index < (int)ft_strlen(token->content))
	{
		if (token->content[index] == 36)
		{
			expand_dollar(&token, envs, &index, 0);
			if (index < 0)
				return (1);
		}
		else if (token->content[index] == 39)
		{
			remove_singles(&token, &index);
			if (index < 0)
				return (1);
			index++;
		}
		else if (token->content[index] == 34)
		{
			remove_doubles(&token, envs, &index);
			if (index < 0)
				return (1);
			index++;
		}
		else
			index++;
	}
	return (0);
}

void	token_touchup(t_toks **tokens, t_env **envs)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		if (token_fucker(&token, envs) > 0)
		{
			ft_lstclear_toks(tokens);
			return ;
		}
		token = token->next;
	}
}
