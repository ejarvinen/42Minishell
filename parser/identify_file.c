/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:08:12 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/07 06:43:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	single_redirs_long_str(t_toks *token, t_toks *next, int type)
{
	if (token->content[0] == type)
	{
		token->file = 1;
		if (next)
			next->file = 0;
	}
	else if (token->content[ft_strlen(token->content) - 1] == type)
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

static void	check_infile_redirection(t_toks *token, t_toks *next)
{
	if (token->in_redir > 0 && ft_strlen(token->content) == 1)
	{
		token->file = 0;
		if (next)
			next->file = 1;
	}
	else if (token->in_redir > 0 && ft_strlen(token->content) > 1)
	{
		single_redirs_long_str(token, next, '<');
	}
	else
		token->file = 0;
}

static void	check_outfile_redirection(t_toks *token, t_toks *next)
{
	if (token->out_redir > 0 && ft_strlen(token->content) == 1)
	{
		token->file = 0;
		if (next)
			next->file = 1;
	}
	else if (token->out_redir > 0 && ft_strlen(token->content) > 1)
	{
		single_redirs_long_str(token, next, '>');
	}
	else
		token->file = 0;
}

static void	double_redirs_long_str(t_toks *token, t_toks *next)
{
	if (ft_strncmp(token->content, ">>", 2) == 0)
	{
		token->file = 1;
		if (next)
			next->file = 0;
	}
	else if (ft_strncmp((token->content + (int)ft_strlen(token->content) - 2), ">>", 2) == 0)
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

static void	check_append(t_toks *token, t_toks *next)
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

static void	add_file_info(t_toks *token, t_toks *next)
{
	int file;

	file = 0;
	check_infile_redirection(token, next);
	file += token->file;
	check_outfile_redirection(token, next);
	file += token->file;
	check_append(token, next);
	file += token->file;
	token->file = file;
}

void	recognize_file(t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;

	token = *tokens;
	if (ft_lstsize_toks(token) > 1)
	{
		next = token->next;
		while (next)
		{
			if (token->file < 1)
				add_file_info(token, next);
			token = token->next;
			next = next->next;
		}
	}
	if (token->file < 1)
		add_file_info(token, NULL);
}
