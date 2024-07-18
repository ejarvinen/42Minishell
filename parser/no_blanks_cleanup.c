/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_blanks_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:12:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 10:03:30 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
splits token into separate tokens is infile, outfile or append
redirects are found
*/
static int	check_for_redirs(t_toks **tokens, t_toks *token)
{
	if (token->in_redir > 0)
	{
		if (split_by_delim(tokens, token, '<', NULL) > 0)
			return (0);
		return (1);
	}
	else if (token->out_redir > 0)
	{
		if (split_by_delim(tokens, token, '>', NULL) > 0)
			return (0);
		return (1);
	}
	else if (token->append > 0)
	{
		if (split_by_delim(tokens, token, 0, ">>") > 0)
			return (0);
		return (1);
	}
	return (0);
}

/*
splits token into separate tokens by delimiter type
*/
static int	check_for_multiple_flags(t_toks **tokens, t_toks *token)
{
	if (token->pipe > 0)
	{
		if (split_by_delim(tokens, token, '|', NULL) > 0)
			return (0);
		return (1);
	}
	else if (check_for_redirs(tokens, token) > 0)
		return (1);
	else if (token->heredoc_delimiter > 0)
	{
		if (split_by_delim(tokens, token, 0, "<<") > 0)
			return (0);
		return (1);
	}
	return (0);
}

/*
cleans up tokens that have multiple flags by splitting by delimiter
*/
void	no_blanks_cleanup(t_toks **tokens, t_mini *shell)
{
	t_toks	*token;
	int		status;

	token = *tokens;
	while (token)
	{
		if (struct_sum(token) != 1)
		{
			status = check_for_multiple_flags(tokens, token);
			if (status < 1)
			{
				syntax_check(NULL, NULL, shell);
				ft_lstclear_toks(tokens);
				return ;
			}
			free(token->content);
			free(token);
			token = *tokens;
			add_indexes(tokens);
			identifier(tokens);
		}
		else
			token = token->next;
	}
}
