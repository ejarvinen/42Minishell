/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:51:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/09 08:21:31 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_mini *shell, int code, int sig)
{
	if (g_sig != sig)
		g_sig = sig;
	shell->EXIT_CODE = code;
}

void	write_exit(t_mini *shell)
{
	int	num;

	if (g_sig != 0)
		num =  g_sig;
	else
		num = shell->EXIT_CODE;
	printf("%d: command not found", num);
	exit_code(shell, 127, 0);
}
