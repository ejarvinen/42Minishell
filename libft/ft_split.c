/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:02:30 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/10 13:13:03 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *str, char c)
{
	size_t	num;
	size_t	i;

	num = 0;
	i = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] != c)
	{
		num++;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			if (str[i - 1] == c)
				num++;
		}
		i++;
	}
	return (num);
}

static size_t	ft_wordlength(const char *str, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static void	*ft_freearray(char **array, size_t j)
{
	size_t	index;

	index = 0;
	while (index <= j)
	{
		free(array[index]);
		index++;
	}
	free(array);
	return (NULL);
}

static char	*ft_strnewcpy(const char *src, char *des, size_t i, size_t length)
{
	size_t	dest;

	dest = 0;
	while (length > 0)
	{
		des[dest] = src[i];
		i++;
		dest++;
		length--;
	}
	des[dest] = '\0';
	return (des);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	size_t		i;
	size_t		j;
	size_t		len;

	array = (char **)malloc((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!array)
		return (0);
	i = 0;
	j = 0;
	while (ft_wordcount(s, c) > j)
	{
		while (s[i] == c)
			i++;
		len = ft_wordlength(s, i, c);
		array[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!array[j])
			return (ft_freearray(array, j));
		array[j] = ft_strnewcpy(s, array[j], i, len);
		i = i + len;
		j++;
	}
	array[j] = 0;
	return (array);
}
