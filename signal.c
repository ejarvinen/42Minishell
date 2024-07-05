/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:24:18 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/05 12:31:16 by sataskin         ###   ########.fr       */
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
static void	child_sig_c(int sig)
{
	g23_sig = sig;
	printf("\n");
}

static void	child_sig_slash(int sig)
{
	g23_sig = sig;
	printf("%s\n", "Quit (core dumped)");
}

void	set_signal(int mode)
{
	struct sigaction	cc;
	struct sigaction	cs;

	ft_memset(&cc, 0, sizeof(cc));
	set_term(mode);
	if (mode == 0)
		cc.sa_handler = par_sig_handler;
	if (mode == 1)
		cc.sa_handler = child_sig_c;
	sigaction(SIGINT, &cc, NULL);
	if (mode == 0)
		cs.sa_handler = SIG_IGN;
	if (mode == 1)
		cs.sa_handler = child_sig_slash;
	sigaction(SIGQUIT, &cs, NULL);
}
