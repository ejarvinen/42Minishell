/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_blanks_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:12:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/14 17:08:11 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
returns the sum of all flags in token
*/
int	struct_sum(t_toks *token)
{
	int	sum;

	sum = token->append + token->argument + token->command + token->file + token->heredoc + token->heredoc_delimiter + token->in_redir + token->out_redir + token->pipe;
	return (sum);
}

/*
adds a new node to the beginning of a list
*/
static void	ft_lstadd_front_toks(t_toks **lst, t_toks *new)
{
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}

/*
adds a node containing the specified delimiter/divider to specified location in list
*/
static int	add_delim_node(t_toks **addition, char delim, char *divid, int location)
{
	t_toks	*delim_node;

	delim_node = NULL;
	if (delim == '|')
		delim_node = ft_lstnew_toks("|");
	else if (delim == '<')
		delim_node = ft_lstnew_toks("<");
	else if (delim == '>')
		delim_node = ft_lstnew_toks(">");
	else if (ft_strncmp(divid, ">>", 2) == 0)
		delim_node = ft_lstnew_toks(">>");
	else if (ft_strncmp(divid, "<<", 2) == 0)
		delim_node = ft_lstnew_toks("<<");
	if (!delim_node)
		return (1);
	if (location == 0)
		ft_lstadd_front_toks(addition, delim_node);
	else
		ft_lstadd_back_toks(addition, delim_node);
	return (0);
}

/*
performs ft_lstclear for list of tokens
*/
static void	clean_up_resources(t_toks **addition)
{
	ft_lstclear_toks(addition);
}

/*
builds a linked list of the splitted token containing a single length delimiter
*/
static void	build_list(t_toks **addition, char *content, char **new_tokens, char delim)
{
	t_toks	*new_node;
	int	item;
	
	item = 0;
	while (new_tokens[item])
	{
		if (item == 0 && content[0] == delim)
		{
			if (add_delim_node(addition, delim, NULL, 0) > 0)
				return (clean_up_resources(addition));
		}
		new_node = ft_lstnew_toks(new_tokens[item]);
		if (!new_node)
			return (clean_up_resources(addition));
		add_token_info(new_node);
		ft_lstadd_back_toks(addition, new_node);
		item++;
		if (new_tokens[item] != NULL && add_delim_node(addition, delim, NULL, 1) > 0)
			return (clean_up_resources(addition));
	}
}

/*
builds a linked list of the splitted token for tokens containing delimiter longer than one char
*/
static void	build_list_delimstr(t_toks **addition, char *content, char **new_tokens, char *delim)
{
	t_toks	*new_node;
	int	item;
	
	item = 0;
	while (new_tokens[item])
	{
		if (item == 0 && ft_strncmp(content, delim, 2) == 0)
		{
			if (add_delim_node(addition, 0, delim, 0) > 0)
				return (clean_up_resources(addition));
		}
		new_node = ft_lstnew_toks(new_tokens[item]);
		if (!new_node)
			return (clean_up_resources(addition));
		add_token_info(new_node);
		ft_lstadd_back_toks(addition, new_node);
		item++;
		if (new_tokens[item] != NULL && add_delim_node(addition, 0, delim, 1) > 0)
			return (clean_up_resources(addition));
	}
}

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
adds a new list of tokens to the existing one according to token position original list
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
splits the multiflagged token by delimeter; returns 1 for errors, zero for success
*/
static int	split_by_delim(t_toks **tokens, t_toks *token, char delim, char *divid)
{
	char	**new_tokens;
	t_toks	*addition;
	t_toks	*head;
	int	lst_size;

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
	free_array(new_tokens);
	if (lst_size > 1)
		add_to_tokens(tokens, token, &addition);
	else
		*tokens = addition;
	return (0);
}

static int	check_for_multiple_flags(t_toks **tokens, t_toks *token)
{
	if (token->pipe == 1)
	{
		if (split_by_delim(tokens, token, '|', NULL) > 0)
			return (0);
		return (1);
	}
	else if (token->in_redir == 1)
	{
		if (split_by_delim(tokens, token, '<', NULL) > 0)
			return (0);
		return (1);
	}
	else if (token->out_redir == 1)
	{
		if (split_by_delim(tokens, token, '>', NULL) > 0)
			return (0);
		return (1);
	}
	else if (token->append == 1)
	{
		if (split_by_delim(tokens, token, 0, ">>") > 0)
			return (0);
		return (1);
	}
	else if (token->heredoc_delimiter == 1)
	{
		if (split_by_delim(tokens, token, 0, "<<") > 0)
			return (0);
		return (1);
	}
	return (0);
}

void	no_blanks_cleanup(t_toks **tokens)
{
	t_toks	*token;
	int	status;

	token = *tokens;
	while (token)
	{
		if (struct_sum(token) != 1)
		{
			status = check_for_multiple_flags(tokens, token);
			if (status < 1)
			{
				ft_lstclear_toks(tokens);
				return ;
			}
			else
			{
				free(token->content);
				free(token);
				token = *tokens;
				add_indexes(tokens);
				identifier(tokens);
			}
		}
		else
			token = token->next;
	}
}
