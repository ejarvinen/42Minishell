/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:22:12 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/08 12:51:33 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	index;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (s[0] == '\0')
		len = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	index = 0;
	if (!str)
		return (0);
	if (start >= ft_strlen(s) && len > 0)
		return (ft_bzero(str, len));
	while (index < len && s[start] != '\0')
	{
		str[index] = s[start];
		index++;
		start++;
	}
	str[index] = '\0';
	return (str);
}
