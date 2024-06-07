/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:09:23 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/03 16:54:46 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *nd, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!hs && len == 0)
		return (NULL);
	if (nd[j] == '\0')
		return ((char *)hs);
	while (hs[i] != '\0' && len > i)
	{
		while (nd[j] == hs[i + j] && hs[i + j] != '\0' && (j + i) < len)
		{
			j++;
			if (nd[j] == '\0')
				return ((char *)&hs[i]);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
