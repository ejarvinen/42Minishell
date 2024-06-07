/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:14:50 by sataskin          #+#    #+#             */
/*   Updated: 2023/10/30 17:19:29 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;

	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	if (!src && !dest)
		return (NULL);
	if (src < dest)
	{
		while (n > 0)
		{
			n--;
			c_dest[n] = c_src[n];
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
