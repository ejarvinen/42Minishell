/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:26:47 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/14 16:01:32 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	index;

	dest_len = 0;
	index = 0;
	if (!dest && n == 0)
		return (0);
	while (dest[dest_len] != '\0' && n > dest_len)
		dest_len++;
	if (n == dest_len)
		return (dest_len + ft_strlen(src));
	while ((dest_len + 1) < n && src[index] != '\0')
	{
		dest[dest_len] = src[index];
		dest_len++;
		index++;
	}
	dest[dest_len] = '\0';
	while (src[index] != '\0')
	{
		index++;
		dest_len++;
	}
	return (dest_len);
}
