/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:56:54 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/03 13:15:07 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		len;
	int		index;

	len = ft_strlen(src);
	index = 0;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (index < len)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
