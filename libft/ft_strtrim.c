/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:04:32 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/18 09:51:47 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	int	index;

	index = 0;
	while (set[index] != 0)
	{
		if (set[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		length;
	int		orig;

	length = ft_strlen(s1);
	orig = 0;
	while (ft_isset(s1[orig], set) != 0 && s1[orig] != '\0')
		orig++;
	if (s1[orig] == '\0')
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	while (ft_isset(s1[length - 1], set) != 0 && (length - 1) > -1)
		length--;
	str = ft_substr(s1, orig, (length - orig));
	return (str);
}
