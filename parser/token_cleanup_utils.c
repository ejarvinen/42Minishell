/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cleanup_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:04:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 13:38:01 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
copies string from to string to while skipping given indexes
*/
void	strcpy_without_quotes(char *to, char *from, int fstquote, int sqnquote)
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
returns index for the matching double quote, expands dollar signs where possible
*/
int	end_quote_index(t_mini *shell, t_toks **token, int *index)
{
	t_toks	*item;
	int		end_quote;

	item = *token;
	end_quote = *index + 1;
	while (item->content[end_quote] != 34 && item->content[end_quote] != '\0')
	{
		if (item->content[end_quote] == 36)
		{
			expand_dollar(shell, token, &end_quote, 1);
			if (end_quote < 0)
				return (-1);
			item = *token;
		}
		else
			end_quote++;
	}
	return (end_quote);
}
