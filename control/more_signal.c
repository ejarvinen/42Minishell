/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:10:18 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/11 11:11:13 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_term(int num)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (num != 0)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
}
