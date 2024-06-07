/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:03:40 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:09:51 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function checks if c is a digit (0-9). Returns 1 if is */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
