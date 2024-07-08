/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:07:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/08 10:58:21 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	par_sig_handler(int sig)
{
	g_sig = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
static void	child_sig_c(int sig)
{
	g_sig = sig;
	printf("^C\n");
}

static void	child_sig_slash(int sig)
{
	g_sig = sig;
	printf("\33[2K\r%s\n", "Quit (core dumped)");
}

static void	heredoc_c(int sig)
{
	g_sig = sig;
	printf("\n");
}

void	set_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, par_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, child_sig_c);
		signal(SIGQUIT, child_sig_slash);
	}
	if (mode == 2)
	{
		signal(SIGINT, heredoc_c);
		signal(SIGQUIT, SIG_IGN);
	}
}
