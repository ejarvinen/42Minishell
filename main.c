/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:04 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/10 11:10:23 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

static int	main_loop(t_mini *shell)
{
	char	*rl;

	set_signal(0);
	//rl = readline("\x1b[95mMINISHELL\x1b[0m💖~$ ");
	rl = readline(PINK PROMPT RESET);
	if (!rl)
		return (1);
	if (rl[0] == '\0')
		return (0);
	set_signal(1);
	if (parser(rl, shell) == 0)
	{
		prep_for_exec(shell);
	}
	close_files(&shell->cmds);
	ft_lstclear_pars(&shell->cmds);
	add_history(rl);
	free(rl);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	static t_mini	shell;

	(void)argv;
	g_sig = 0;
	if (argc != 1)
	{
		printf("Run minishell using only <./minishell>\n");
		exit (1);
	}
	set_data(&shell, envp);
	while (1)
	{
		if (main_loop(&shell) > 0)
			break ;
	}
	free_data(&shell, "exit\n");
	return (0);
}
