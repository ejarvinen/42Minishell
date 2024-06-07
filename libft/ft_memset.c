/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:11:06 by sataskin          #+#    #+#             */
/*   Updated: 2023/10/30 17:19:31 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	index;
	char	*string;

	string = s;
	index = 0;
	while (index < n)
	{
		*string = c;
		index++;
		string++;
	}
	return (s);
}
