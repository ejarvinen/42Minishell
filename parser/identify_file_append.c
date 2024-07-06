/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_file_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:41:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 14:42:51 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
updates file info when token contains more than just the append delimiter
*/
static void	double_redirs_long_str(t_toks *token, t_toks *next)
{
	if (ft_strncmp(token->content, ">>", 2) == 0)
	{
		token->file = 1;
		if (next)
			next->file = 0;
	}
	else if (ft_strncmp((token->content
				+ (int)ft_strlen(token->content) - 2), ">>", 2) == 0)
	{
		if (next)
			next->file = 1;
		token->file = 0;
	}
	else
	{
		token->file = 1;
		token->argument = 1;
	}
}

/*
checks if token contains append delimiter
*/
void	check_append(t_toks *token, t_toks *next)
{
	if (token->append > 0 && ft_strlen(token->content) == 2)
	{
		token->file = 0;
		if (next)
			next->file = 1;
	}
	else if (token->append > 0 && ft_strlen(token->content) > 2)
	{
		double_redirs_long_str(token, next);
	}
	else
		token->file = 0;
}
