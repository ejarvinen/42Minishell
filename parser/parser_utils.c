/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:04:43 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 14:10:41 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
writes the given str to STDERR
*/
void	parser_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(str, 2);
}

int	funtastic(t_mini *shell)
{
	parser_error("malloc fail");
	exit_code(shell, 1, 0);
	ft_lstclear_pars(&shell->cmds);
	return (1);
}

/*
returns the sum of all flags in token
*/
int	struct_sum(t_toks *token)
{
	int	sum;

	sum = token->append + token->argument + token->command + token->file
		+ token->heredoc + token->heredoc_delimiter + token->in_redir
		+ token->out_redir + token->pipe;
	return (sum);
}

/*
identifies expandable by white space, quotes and key name requirements
*/
int	identify_expandable(char *token)
{
	int	index;

	index = 0;
	while (token[index] != '\0' && token[index] != 34
		&& token[index] != 39 && token[index] != 32
		&& (ft_isalnum(token[index]) == 1 || token[index] == '_'))
		index++;
	return (index);
}

/*
returns the node containing key var; if key is not found, returns NULL
*/
t_env	*key_finder(char *var, t_env **envs)
{
	t_env	*env;
	size_t	var_len;

	env = *envs;
	var_len = ft_strlen(var);
	while (env)
	{
		if (var_len == ft_strlen(env->key)
			&& ft_strncmp(var, env->key, var_len) == 0)
		{
			if (!env->value[0] || !env->value)
				return (NULL);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}
