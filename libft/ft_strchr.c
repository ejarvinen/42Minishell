/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:04:43 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/07 17:32:19 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	u_c;
	unsigned char	*s;

	i = 0;
	u_c = (unsigned char)c;
	s = (unsigned char *)str;
	while (s[i] != '\0' && s[i] != u_c)
		i++;
	if (s[i] == u_c)
		return ((char *)&str[i]);
	return (NULL);
}
