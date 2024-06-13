/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:26:07 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/13 11:01:10 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
initializes default token info
*/
void	add_token_info(t_toks *new_node)
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
adds a new token to list of tokens
*/
static int	add_new_token(char *token, t_toks **tokens)
{
	t_toks	*new_token;

	new_token = ft_lstnew_toks(token);
	if (!new_token)
	{
		perror("minishell");
		return (1);
	}
	add_token_info(new_token);
	ft_lstadd_back_toks(tokens, new_token);
	return (0);
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
static int	quote_check(char *token)
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

void	add_indexes(t_toks **tokens)
{
	t_toks	*token;
	int	index;

	token = *tokens;
	index = 0;
	while (token)
	{
		token->id = index;
		index++;
		token = token->next;
	}
}

t_toks	*checker(char *input)
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
			{
				free(rl);
				if (tokens != NULL)
					ft_lstclear_toks(&tokens);
				return (NULL);
			}
		}
		else
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			free(rl);
			if (tokens != NULL)
				ft_lstclear_toks(&tokens);
			return (NULL);
		}
		token = ft_strtok(NULL);
	}
	free(rl);
	add_indexes(&tokens);
	return (tokens);
}

//exit(258); exit code for command not found or maybe it was syntax error, who the fuck knows at this point....
