/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:24:18 by sataskin          #+#    #+#             */
/*   Updated: 2024/05/30 13:57:25 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_term(int num)
{
	struct termios    term;

    tcgetattr(STDIN_FILENO, &term);
    if (num == 1)
        term.c_lflag |= ECHOCTL;
    else
        term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDERR_FILENO, TCSANOW, &term);
}

void	par_sig_handler(int sig)
{
	g23_sig = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(int mode)
{
	struct sigaction	cc;
	struct sigaction	cs;

	ft_memset(&cc, 0, sizeof(cc));
	set_term(mode);
	if (mode == 0) 
		cc.sa_handler = par_sig_handler;
	else
		exit (1);
	sigaction(SIGINT, &cc, NULL);
	cs.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &cs, NULL);
}
