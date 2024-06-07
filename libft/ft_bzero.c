/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:02:06 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 13:58:25 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* It creates a string of size n and fills it with zeros */

void	*ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return (s);
}
