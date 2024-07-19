/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_blanks_cleanup_list_tools.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:09:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/19 14:45:31 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
adds a node containing the specified delimiter/divider to specified
location in list
*/
static int	add_delim_node(t_toks **addition, char delim,
char *divid, int location)
{
	t_toks	*delim_node;

	delim_node = NULL;
	if (delim == '|')
		delim_node = ft_lstnew_toks("|");
	else if (delim == '<')
		delim_node = ft_lstnew_toks("<");
	else if (delim == '>')
		delim_node = ft_lstnew_toks(">");
	else if (ft_strcmp(divid, ">>") == 0)
		delim_node = ft_lstnew_toks(">>");
	else if (ft_strcmp(divid, "<<") == 0)
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
void	build_list(t_toks **addition, char *content,
char **new_tokens, char delim)
{
	t_toks	*new_node;
	int		item;

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
		initialize_token(new_node);
		ft_lstadd_back_toks(addition, new_node);
		item++;
		if (new_tokens[item] != NULL
			&& add_delim_node(addition, delim, NULL, 1) > 0)
			return (clean_up_resources(addition));
		else if (new_tokens[item] == NULL
			&& content[ft_strlen(content) - 1] == delim
			&& add_delim_node(addition, delim, NULL, 1) > 0)
			return (clean_up_resources(addition));
	}
}

/*
builds a linked list of the splitted token for tokens containing delimiter
longer than one char
*/
void	build_list_delimstr(t_toks **addition, char *content,
char **new_tokens, char *delim)
{
	t_toks	*new_node;
	int		item;

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
		initialize_token(new_node);
		ft_lstadd_back_toks(addition, new_node);
		item++;
		if (new_tokens[item] != NULL
			&& add_delim_node(addition, 0, delim, 1) > 0)
			return (clean_up_resources(addition));
	}
}
