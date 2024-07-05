/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:04 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/05 12:18:55 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g23_sig;

int main(int argc, char **argv, char **envp)
{
	char	*rl;
	static t_mini	shell;

	(void)argv;
	g23_sig = 0;
	if (argc != 1)
	{
		printf("Run minishell using only <./minishell>\n");
		exit (1);
	}
	set_data(&shell, envp);
	while (1)
	{
		set_signal(0);
   	 	rl = readline("\x1b[95mMINISHELL\x1b[0m💖~$ ");
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		set_signal(1);
		if (parser(rl, &shell) == 0)
		{
			prep_for_exec(&shell);
		}
		close_files(&shell.cmds);
		ft_lstclear_pars(&shell.cmds);
		add_history(rl);
		free(rl);
	}
	free_data(&shell, "exit\n");
	return (0);
}
