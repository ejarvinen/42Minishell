/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:20:54 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:25:44 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function looks for the first occurrence of char c in the first bytes
n. It returns a pointer to the first occurrence or a NULL. */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*temp;
	unsigned char	u_c;

	temp = (unsigned char *)s;
	index = 0;
	u_c = (unsigned char)c;
	while (index < n)
	{
		if (temp[index] == u_c)
			return ((void *)&s[index]);
		index++;
	}
	return (NULL);
}
