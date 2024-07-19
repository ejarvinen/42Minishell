/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:53:29 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/19 12:11:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	real_exit(t_mini *shell, char *str, int i)
{
	char	*check;

	if (i > 0)
	{
		free_data(shell, NULL);
		exit (i);
	}
	i = ft_atoi(str);
	check = ft_itoa(i);
	if (check == NULL)
	{
		free_data(shell, NULL);
		exit(1);
	}
	if (exit_strcmp(check, str) != 0)
	{
		free(check);
		print_letter(shell, str);
	}
	free(check);
	free_data(shell, NULL);
	ft_putstr_fd("exit\n", 1);
	exit (i);
}

void	print_toomany(t_mini *shell)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putendl_fd("too many arguments", 2);
	exit_code(shell, 1, 0);
}

void	print_letter(t_mini *shell, char *str)
{
	printf("exit\n");
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	real_exit(shell, str, 2);
}

int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

void	now_exit(t_mini *shell, char **str)
{
	if (str[1] != NULL)
	{
		if (check_num(str[1]) == 1)
			print_letter(shell, str[1]);
		if (str[2] != NULL)
			print_toomany(shell);
		else
			real_exit(shell, str[1], 0);
	}
	else
		real_exit(shell, "0", 0);
}
