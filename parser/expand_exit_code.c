/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:19:52 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 13:38:42 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_exit_code(t_toks **tokens, t_mini *shell)
{
	t_toks	*token;
	char	*freeable;

	token = *tokens;
	while (token)
	{
		if (ft_strcmp(token->content, "$?") == 0 && token->command == 0)
		{
			freeable = token->content;
			token->content = ft_itoa(shell->exit_code);
			if (!token->content)
			{
				ft_lstclear_toks(tokens);
				return ;
			}
			free(freeable);
		}
		token = token->next;
	}
}

int	is_expandable(int c)
{
	if (c == 0 || c == 32 || c == 9 || c == 34 || c == 39)
		return (1);
	return (0);
}

static void	erase_question_mark(char *new_token, char *token, char *code, int start)
{
	int	index;
	int	cindex;
	int	tindex;

	index = 0;
	while (index < start)
	{
		new_token[index] = token[index];
		index++;
	}
	cindex = 0;
	while (code[cindex] != '\0')
	{
		new_token[index] = code[cindex];
		index++;
		cindex++;
	}
	tindex = start + 2;
	while (token[tindex] != '\0')
	{
		new_token[index] = token[tindex];
		index++;
		tindex++;
	}
	new_token[index] = '\0';
}

char	*expand_exitcode(t_mini *shell, char *str, int *index)
{
	char	*e_code;
	char	*new_token;

	e_code = ft_itoa(shell->exit_code);
	if (!e_code)
	{
		*index = -1;
		return (NULL);
	}
	new_token = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(e_code)));
	if (!new_token)
	{
		*index = -1;
		return (NULL);
	}
	erase_question_mark(new_token, str, e_code, *index);
	return (new_token);
}
