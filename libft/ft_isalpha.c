/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:15:48 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/09 14:18:16 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function checks if c is a letter. If this is the case
it returns 1 */

int	ft_isalpha(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		return (1);
	else
		return (0);
}
