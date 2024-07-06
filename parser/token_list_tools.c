/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:08:20 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 13:10:10 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
initializes default token info
*/
void	initialize_token(t_toks *new_node)
{
	new_node->argument = -1;
	new_node->command = -1;
	new_node->file = -1;
	new_node->heredoc = -1;
	new_node->heredoc_delimiter = -1;
	new_node->in_redir = -1;
	new_node->out_redir = -1;
	new_node->append = -1;
	new_node->pipe = -1;
	new_node->id = -1;
}

/*
returns the number of quotes in str according to type quote
*/
static int	quote_count(char const *str, int quote)
{
	int	index;
	int	quotes;

	quotes = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == quote)
			quotes++;
		index++;
	}
	return (quotes);
}

/*
checks for even number of quotes in token according to first type of quote found
*/
int	quote_check(char *token)
{
	int	quotes;
	
	quotes = 0;
	if (token[0] == 39 || token[0] == 34)
	{
		if (token[0] == 39)
			quotes = quote_count(token, 39);
		else if (token[0] == 34)
			quotes = quote_count(token, 34);
		if (quotes % 2 == 0)
			return (1);
		return (0);
	}
	else
		return (1);
}
