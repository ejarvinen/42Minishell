/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:45:57 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/16 13:22:45 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_validerror(char *mes, char *func)
{
	printf("minishell: %s: `%s\': not a valid identifier\n", func, mes);
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
	ft_validerror(str, function);
	return (1);
}
