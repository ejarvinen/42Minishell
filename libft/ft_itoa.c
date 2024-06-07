/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:55:40 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:17:11 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates memory with malloc and makes a string representing an integer
received as an argument. 
ft_intlen calculates the length of the string needed to be made.
ft_itoa then makes the string and adds in the characters */

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n = n * (-1);
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_intlen(n);
	if (len == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * ((size_t)len + 1));
	if (!str)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
	}
	str[len] = '\0';
	len--;
	while (n > 0)
	{
		str[len] = '0' + (n % 10);
		n = n / 10;
		len--;
	}
	return (str);
}
