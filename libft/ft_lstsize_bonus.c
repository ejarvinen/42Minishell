/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:12:21 by sataskin          #+#    #+#             */
/*   Updated: 2024/02/09 13:28:40 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
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
