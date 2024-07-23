/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:19:52 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/23 10:56:24 by sataskin         ###   ########.fr       */
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
			if (g_sig > 0)
				token->content = ft_itoa(128 + g_sig);
			else
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

static void	erase_question_mark(char *new_token, char *token, char *code,
int start)
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

static char	*expand_exitcode(t_mini *shell, char *str, int *index)
{
	char	*e_code;
	char	*new_token;
	size_t	new_len;

	e_code = ft_itoa(shell->exit_code);
	if (!e_code)
	{
		*index = -1;
		return (NULL);
	}
	new_len = ft_strlen(str) + ft_strlen(e_code);
	new_token = (char *)malloc(sizeof(char) * (new_len - 1));
	if (!new_token)
	{
		*index = -1;
		return (NULL);
	}
	erase_question_mark(new_token, str, e_code, *index);
	return (new_token);
}

int	identify_exitcode(t_mini *shell, t_toks **token, int *index, int in_doubles)
{
	char	*freeable;
	t_toks	*item;

	item = *token;
	if (ft_strcmp(item->content, "$?") == 0)
	{
		*index = *index + 2;
		return (1);
	}
	else if (ft_strncmp(item->content + *index, "$?", 2) == 0)
	{
		freeable = item->content;
		item->content = expand_exitcode(shell, item->content, index);
		if (!item->content)
		{
			*index = -1;
			return (1);
		}
		if (in_doubles == 1)
			(*index)++;
		free(freeable);
		return (1);
	}
	return (0);
}
