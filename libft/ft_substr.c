/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:22:12 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 13:05:52 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_substr(char *substr, char const *s,
		unsigned int start, size_t len)
{
	size_t	index;
	size_t	slen;

	index = 0;
	slen = ft_strlen(s);
	while (index < len && start + index < slen)
	{
		substr[index] = s[start + index];
		index++;
	}
	substr[index] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (s)
	{
		slen = ft_strlen(s);
		if (len > (slen - start))
			len = slen - start;
		if (start >= MAX_ULONG || slen <= start || len == 0)
			return (ft_strdup(""));
		else if (slen >= (start + len))
			substr = (char *)malloc(len * sizeof(char) + 1);
		else
			substr = (char *)malloc((slen - start) * sizeof(char) + 1);
		if (!substr)
			return (NULL);
		return (create_substr(substr, s, start, len));
	}
	return (NULL);
}
