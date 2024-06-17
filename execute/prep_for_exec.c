/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_for_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:09:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/17 08:23:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_builtin(t_mini *shell, char **str)
{
	int error;
	
	if (str[0] == NULL)
		return ;
	if (ft_strcmp(str[0], "export") == 0)
		export(&shell->env, str, shell->cmds->fd_outfile);
	else if (ft_strcmp(str[0], "unset") == 0)
		ft_unset(&shell->env, str);
	else if (ft_strcmp(str[0], "env") == 0)
		error = ft_env(shell);
	else if (ft_strcmp(str[0], "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(str[0], "cd") == 0)
		ft_cd(shell, str[1]);
	else if (ft_strcmp(str[0], "echo") == 0)
		printf("not made echo yet\n");
	else if (ft_strcmp(str[0], "exit") == 0)
		now_exit(shell, str);
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

void	prep_for_exec(t_mini *shell)
{
	open_files(&shell->cmds);
	print_cmd_info(&shell->cmds);
	check_builtin(shell, shell->cmds->command);
//	nonexistent_cmd(&shell->cmds);
//	dot_cmd(&shell->cmds);
	if (shell->cmds->fd_infile == -1)
	{}
}
