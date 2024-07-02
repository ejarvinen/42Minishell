/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:20:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/02 07:21:47 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_long_str(t_toks *token, t_toks *next)
{
	if (ft_strncmp(token->content, "<<", 2) == 0)
	{
		token->heredoc = 1;
		if (next)
			next->heredoc = 0;
	}
	else if (ft_strncmp((token->content + (int)ft_strlen(token->content) - 2), "<<", 2) == 0)
	{
		if (next)
			next->heredoc = 1;
		token->heredoc = 0;
	}
	else
	{
		token->heredoc = 1;
		token->command = 1;
	}
}

static void	check_heredoc(t_toks *token, t_toks *next)
{
	if (token->heredoc_delimiter > 0 && ft_strlen(token->content) == 2)
	{
		token->heredoc = 0;
		if (next)
			next->heredoc = 1;
	}
	else if (token->heredoc_delimiter > 0 && ft_strlen(token->content) > 2)
	{
		heredoc_long_str(token, next);
	}
	else
	{
		token->heredoc = 0;
		if (next)
			next->heredoc = 0;
	}
}

void	identify_heredoc(t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;

	token = *tokens;
	if (ft_lstsize_toks(token) > 1)
	{
		next = token->next;
		while (next)
		{
			if (token->heredoc < 1)
				check_heredoc(token, next);
			token = token->next;
			next = next->next;
		}
	}
	if (token->heredoc < 1)
		check_heredoc(token, NULL);
}

static int	check_for_previous_cmds(t_toks **tokens, int index)
{
	int	cmds;
	t_toks	*token;

	token = *tokens;
	cmds = 0;
	while (token->id != index - 1)
	{
		if (token->pipe > 0)
			cmds = 0;
		else if (token->command > 0)
			cmds++;
		token = token->next;
	}
	return (cmds);
}

static void	check_for_cmd_indicators(t_toks **tokens, t_toks *token, t_toks *next)
{
	if (token->pipe > 0 && ft_strlen(token->content) == 1)
	{
		token->command = 0;
		if (next)
			next->command = 1;
	}
	else if (token->pipe > 0 && ft_strlen(token->content) > 1)
	{
		token->command = 1;
		if (next)
			next->command = 0;
	}
	else if (next && check_for_previous_cmds(tokens, next->id) == 0 && token->append < 1 && token->in_redir < 1 && token->out_redir < 1 && token->heredoc_delimiter < 1 && token->file < 1)
	{
		token->command = 1;
		next->command = 0;
	}
	else
		token->command = 0;
}

void	identify_commands(t_toks **tokens)
{
	t_toks	*token;
	t_toks	*next;
	
	token = *tokens;
	if (ft_lstsize_toks(token) == 1)
	{
		token->command = 1;
		return ;
	}
	next = token->next;
	while (next)
	{
		if (token->command < 1)
			check_for_cmd_indicators(tokens, token, next);
		token = token->next;
		next = next->next;
	}
	if (token->command < 1)
		check_for_cmd_indicators(tokens, token, NULL);
}

void	identify_args(t_toks **tokens)
{
	t_toks	*token;
	
	token = *tokens;
	while (token)
	{
		if (token->argument < 0)
		{
			if (token->id != 0 && token->append < 1 && token->file < 1 && token->heredoc < 1 && token->heredoc_delimiter < 1 && token->in_redir < 1 && token->out_redir < 1 && token->command < 1 && token->pipe < 1)
				token->argument = 1;
			else
				token->argument = 0;
		}
		token = token->next;
	}
}

static void	add_pipe_info(t_toks *token)
{
	token->pipe = 1;
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->append = 0;
}

static void	add_inredir_info(t_toks *token)
{
	token->pipe = 0;
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 1;
	token->out_redir = 0;
	token->append = 0;
}

static void	add_outredir_info(t_toks *token)
{
	token->pipe = 0;
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 1;
	token->append = 0;
}

static void	add_append_info(t_toks *token)
{
	token->pipe = 0;
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->append = 1;
}

static void	add_hredir_info(t_toks *token)
{
	token->pipe = 0;
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 1;
	token->in_redir = 0;
	token->out_redir = 0;
	token->append = 0;
}

static void	double_check(t_toks **tokens)
{
	t_toks	*token;
	
	token = *tokens;
	if (ft_lstsize_toks(token) == 1)
		return ;
	while (token)
	{
		if (struct_sum(token) != 1)
		{
			if (ft_strncmp(token->content, "|", 1) == 0 && ft_strlen(token->content) == 1)
				add_pipe_info(token);
			else if (ft_strncmp(token->content, "<", 1) == 0 && ft_strlen(token->content) == 1)
				add_inredir_info(token);
			else if (ft_strncmp(token->content, ">", 1) == 0 && ft_strlen(token->content) == 1)
				add_outredir_info(token);
			else if (ft_strncmp(token->content, ">>", 2) == 0 && ft_strlen(token->content) == 2)
				add_append_info(token);
			else if (ft_strncmp(token->content, "<<", 2) == 0 && ft_strlen(token->content) == 2)
				add_hredir_info(token);
		}
		token = token->next;
	}
}

void	identifier(t_toks **tokens)
{
	identify_delims(tokens);
	identify_heredoc(tokens);
	recognize_file(tokens);
	identify_commands(tokens);
	identify_args(tokens);
	double_check(tokens);
}
