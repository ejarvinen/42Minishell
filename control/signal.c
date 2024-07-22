/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:07:15 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/22 13:43:20 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	par_sig_handler(int sig)
{
	if (sig)
	{
		g_sig = sig;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	child_sig_c(int sig)
{
	if (sig)
	{
		g_sig = sig;
		printf("\n");
	}
}

static void	child_sig_slash(int sig)
{
	if (sig)
	{
		g_sig = sig;
		printf("%s\n", "Quit (core dumped)");
	}
}

static void	heredoc_c(int sig)
{
	if (sig)
	{
		g_sig = sig;
		printf("\n");
		close(STDIN_FILENO);
	}
}

void	set_signal(int mode)
{
	set_term(mode);
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
	if (mode == 3)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
