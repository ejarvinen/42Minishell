/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:20:25 by emansoor          #+#    #+#             */
/*   Updated: 2024/01/11 07:28:01 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	j;

	j = 0;
	while (str[j] != 0)
		j++;
	return (j);
}

static size_t	copy_fststring(char const *s1, char *jointstr)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		jointstr[i] = s1[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jointstr;
	size_t	i;
	size_t	j;
	size_t	totlen;

	if (s1)
	{
		totlen = ft_strlen(s1) + ft_strlen(s2);
		jointstr = (char *)malloc(sizeof(char) * (totlen + 1));
		if (jointstr)
		{
			i = copy_fststring(s1, jointstr);
			j = 0;
			while (s2[j] != '\0')
			{
				jointstr[i] = s2[j];
				i++;
				j++;
			}
			jointstr[i] = '\0';
			return (jointstr);
		}
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*temp;

	temp = (char *)s;
	while (0 < n)
	{
		temp[n - 1] = '\0';
		n--;
	}
}

int	newline_finder(char *buff, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (buff[index] == 10)
			return (1);
		index++;
	}
	return (0);
}
