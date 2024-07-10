/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:45:57 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 17:13:51 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_validerror(char *mes, char *func)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(mes, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	validity(char *str, char *function)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
	{
		ft_validerror(str, function);
		return (1);
	}
	while (ft_isalnum(str[i]) == 1 || str[i] == '_')
		i++;
	if (str[i] == '\0' || str[i] == '=')
		return (0);
	if (function[0] != 'u')
		ft_validerror(str, function);
	return (1);
}
