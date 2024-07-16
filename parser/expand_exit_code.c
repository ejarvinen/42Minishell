/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:19:52 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/16 10:27:08 by emansoor         ###   ########.fr       */
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
