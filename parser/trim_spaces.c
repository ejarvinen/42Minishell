/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:56:00 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/20 15:56:46 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_empty(t_toks **tokens)
{
	t_toks	*prev;
	t_toks	*next;
	t_toks	*node;

	prev = *tokens;
	while (prev && prev->content[0] == '\0')
	{
		*tokens = prev->next;
		free(prev->content);
		free(prev);
		prev = *tokens;
	}
	while (prev)
	{
		if (prev->next && prev->next->content[0] == '\0')
		{
			node = prev->next;
			next = node->next;
			prev->next = next;
			free(node->content);
			free(node);
		}
		else
			prev = prev->next;
	}
}

void	trim_token(t_toks **token)
{
	t_toks	*temp;
	char	*new;

	temp = *token;
	while (temp != NULL)
	{
		new = temp->content;
		temp->content = ft_strtrim(new, " \t");
		if (!temp->content)
		{
			ft_lstclear_toks(token);
			return ;
		}
		free(new);
		temp = temp->next;
	}
	remove_empty(token);
}
