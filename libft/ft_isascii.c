/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:34:04 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:08:16 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This functions checks if c is a value that fits into the ASCII
character set */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
