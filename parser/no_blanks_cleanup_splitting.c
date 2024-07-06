/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_blanks_cleanup_splitting.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:01:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 16:46:03 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds a new list to the beginning of the existing list
*/
static void	add_to_beginning(t_toks **tokens, t_toks **addition)
{
	t_toks	*tok;
	t_toks	*add;
	t_toks	*temp;
	t_toks	*next;

	tok = *tokens;
	add = *addition;
	next = NULL;
	temp = tok;
	if (temp->next != NULL)
		next = temp->next;
	while (add->next)
		add = add->next;
	add->next = next;
	tok = *addition;
	*tokens = tok;
}

/*
adds a new list to the existing one when token_id > 0
*/
static void	add_to_list(t_toks **tokens, t_toks *token, t_toks **addition)
{
	t_toks	*tok;
	t_toks	*add;
	t_toks	*temp;
	t_toks	*next;
	t_toks	*last;

	tok = *tokens;
	add = *addition;
	next = NULL;
	while (tok->id != token->id - 1)
		tok = tok->next;
	temp = tok->next;
	if (temp->next != NULL)
		next = temp->next;
	tok->next = add;
	if (next != NULL)
	{
		last = ft_lstlast_toks(add);
		last->next = next;
	}
}

/*
adds a new list of tokens to the existing one according to token
position original list
*/
static void	add_to_tokens(t_toks **tokens, t_toks *token, t_toks **addition)
{
	if (token->id == 0)
		add_to_beginning(tokens, addition);
	else
		add_to_list(tokens, token, addition);
}

/*
splits the token string according to the delimeter type
*/
static char	**get_new_tokens(char *token, char delim, char *divid)
{
	char	**new_tokens;

	if (divid == NULL)
		new_tokens = ft_split(token, delim);
	else
		new_tokens = ft_splitstr(token, divid);
	return (new_tokens);
}

/*
splits the multiflagged token by delimeter; returns 1 for errors,
zero for success
*/
int	split_by_delim(t_toks **tokens, t_toks *token, char delim, char *divid)
{
	char	**new_tokens;
	t_toks	*addition;
	t_toks	*head;
	int		lst_size;

	new_tokens = get_new_tokens(token->content, delim, divid);
	if (!new_tokens)
		return (1);
	addition = NULL;
	head = *tokens;
	lst_size = ft_lstsize_toks(head);
	if (divid == NULL)
		build_list(&addition, token->content, new_tokens, delim);
	else
		build_list_delimstr(&addition, token->content, new_tokens, divid);
	if (!addition)
		return (1);
	ft_freearray(new_tokens);
	if (lst_size > 1)
		add_to_tokens(tokens, token, &addition);
	else
		*tokens = addition;
	return (0);
}
