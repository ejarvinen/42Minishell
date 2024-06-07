/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:55:21 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/14 17:35:24 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function checks whether c is a printable character */
int	ft_isprint(int c)
{
	if (c < 127 && c >= 32)
		return (1);
	else
		return (0);
}
