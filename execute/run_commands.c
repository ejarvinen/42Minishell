/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:22:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 11:13:40 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_builtin(t_mini *shell, t_cmds *cmd)
{
	int error;
	
	if (cmd->command[0] == NULL)
		return ;
	if (ft_strcmp(cmd->command[0], "export") == 0)
		export(&shell->env, cmd->command, cmd->fd_outfile);
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		ft_unset(&shell->env, cmd->command);
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		error = ft_env(shell);
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		pwd(shell);
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		ft_cd(shell, cmd->command);
	else if (ft_strcmp(cmd->command[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		now_exit(shell, cmd->command);
	else if (ft_strcmp(cmd->command[0], "test") == 0)
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
	shell->EXIT_CODE = error;
}

static void	run_single(t_mini *shell, t_cmds *cmd)
{
	char	**env;
	t_env	**envs;

	envs = shell->env;
	env = ltoa(*envs);
	if (!env)
		return ;
	cmd->c_pid = fork();
	if (cmd->c_pid < 0)
	{
		perror("minishell");
		return ;
	}
	if (cmd->c_pid == 0)
	{
		execute_single(shell, env, cmd);
	}
}

void	run_commands(t_mini *shell)
{
	t_cmds	*cmds;
	
	cmds = shell->cmds;
	if (cmds->commands == 1)
	{
		if (cmds->builtin == 1)
			check_builtin(shell, cmds);
		else
			run_single(shell, cmds);
	}
	while (cmds)
	{
		
	}
}
