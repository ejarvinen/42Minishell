/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:30:39 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/15 14:22:54 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	void	*cont;
	t_list	*loc;

	if (!lst || !(f) || !(del))
		return (0);
	loc = NULL;
	while (lst)
	{
		cont = f(lst->content);
		temp = ft_lstnew(cont);
		if (!temp)
		{
			del(cont);
			ft_lstclear(&loc, del);
			return (0);
		}
		ft_lstadd_back(&loc, temp);
		lst = lst->next;
	}
	return (loc);
}
