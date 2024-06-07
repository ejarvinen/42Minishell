/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:34:23 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:27:52 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function checks if the value in this case is either a letter or
a number. If this is the case it returns 1 */

int	ft_isalnum(int value)
{
	if (ft_isalpha(value) == 1 || ft_isdigit(value) == 1)
		return (1);
	else
		return (0);
}
