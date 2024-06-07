/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:04 by sataskin          #+#    #+#             */
/*   Updated: 2024/06/07 13:39:05 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_builtin(t_mini *shell, char **str)
{
	int error;
	
	if (str[0] == NULL)
		return ;
	if (ft_strcmp(str[0], "export") == 0)
		export(&shell->env, str);
	else if (ft_strcmp(str[0], "unset") == 0)
		ft_unset(&shell->env, str);
	else if (ft_strcmp(str[0], "env") == 0)
		error = ft_env(shell->env);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(str[0], "cd") == 0)
		ft_cd(shell, str[1]);
	else if (ft_strcmp(str[0], "echo") == 0)
		printf("not made echo yet\n");
	else if (ft_strcmp(str[0], "exit") == 0)
	{
		ft_freearray(str);
		free_env(shell->env);
		exit (0);
	}
	else if (ft_strcmp(str[0], "test") == 0)
	{
		char **str = ltoa(shell->env);
		int i = 0;
		while (str[i] != NULL)
		{
			printf("%s\n", str[i]);
			i++;
		}
		ft_freearray(str);
	}
	else
	{
		printf("what are you typing bro?\n");
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_mini	shell;

	(void)argv;
	if (argc != 1)
	{
		printf("Run minishell using only <./minishell>\n");
		exit (1);
	}
	set_data(&shell, envp);
	while (1)
	{
		set_signal(0);
    		rl = readline("\x1b[95mMINISHELL💖~$ ");
		if (!rl)
			break ;
		if (rl[0] == '\0')
			continue ;
		if (parser(rl, &shell) == 0)
			check_builtin(&shell, shell.cmds->command);
		add_history(rl);
		free(rl);
	}
	free_data(&shell);
	printf("exit\n");
    return (0);
}
