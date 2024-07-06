/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_delims_set_token_specs.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:21:38 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/06 14:22:54 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
sets everything else in token to zero except for pipe
*/
void	sure_pipe(t_toks *token)
{
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
sets everything else to zero in token except for in_redir flag
*/
void	sure_inredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->out_redir = 0;
	token->append = 0;
	token->pipe = 0;
}

/*
sets everything else to zero in token except for out_redir flag
*/
void	sure_outredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->append = 0;
	token->pipe = 0;
}

/*
sets everything to zero in token except for append flag
*/
void	sure_append(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->heredoc_delimiter = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->pipe = 0;
}

/*
sets everything to zero in token except for heredoc_delim flag
*/
void	sure_hredir(t_toks *token)
{
	token->argument = 0;
	token->command = 0;
	token->file = 0;
	token->heredoc = 0;
	token->in_redir = 0;
	token->out_redir = 0;
	token->pipe = 0;
	token->append = 0;
}
