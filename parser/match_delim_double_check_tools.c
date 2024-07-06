/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_delim_double_check_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:37:29 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 15:38:16 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
changes all token flags to zero except pipe
*/
void	add_pipe_info(t_toks *token)
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

/*
changes all token flags to zero except infile redirection
*/
void	add_inredir_info(t_toks *token)
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

/*
changes all token flags to zero except outfile redirection
*/
void	add_outredir_info(t_toks *token)
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

/*
changes all token flags to zero except append
*/
void	add_append_info(t_toks *token)
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

/*
changes all token flags to zero except heredoc_delimiter
*/
void	add_hredir_info(t_toks *token)
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
