/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_toks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:49:43 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/06 08:16:15 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_toks(t_toks **lst, t_toks *new)
{
	t_toks	*node;

	node = *lst;
	if (!new)
		return ;
	else if (*lst == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

void	ft_lstclear_toks(t_toks **lst, void (*del)(void *))
{
	t_toks	*clr;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		clr = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = clr;
	}
	*lst = NULL;
}

t_toks	*ft_lstnew_toks(void *content)
{
	t_toks	*new_node;

	new_node = (t_toks *)malloc(sizeof(t_toks));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	if (!new_node->content)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstsize_toks(t_toks *lst)
{
	int	len;

	len = 1;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_toks	*ft_lstlast_toks(t_toks *lst)
{
	if (!lst)
		return (NULL);
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}
