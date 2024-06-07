/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:17:29 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/07 17:33:48 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t			i;
	signed char		u_c;
	unsigned char	*s;

	i = ft_strlen(str);
	u_c = (unsigned char)c;
	s = (unsigned char *)str;
	while (i != 0 && s[i] != u_c)
		i--;
	if (s[i] == u_c)
		return ((char *)&str[i]);
	return (NULL);
}
