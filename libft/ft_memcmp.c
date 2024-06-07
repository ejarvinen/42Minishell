/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:07:55 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:45:53 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c_s1;
	unsigned char	*c_s2;
	size_t			index;

	index = 0;
	if (n == 0)
		return (0);
	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	while (c_s1[index] == c_s2[index] && n - 1 > index)
		index++;
	return (c_s1[index] - c_s2[index]);
}
