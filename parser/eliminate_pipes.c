/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eliminate_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:12:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/07 07:02:33 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	struct_sum(t_toks *token)
{
	int	sum;

	sum = token->append + token->argument + token->command + token->file + token->heredoc + token->heredoc_delimiter + token->in_redir + token->out_redir + token->pipe;
	return (sum);
}

/*static int	delim_count(char *token, int type)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (token[index] != '\0')
	{
		if (token[index] == type)
		{
			if (in_quotes(token, index) == 0)
				count++;
		}
		index++;
	}
	return (count);
}*/

static void	build_list(t_toks **addition, char **new_tokens)
{
	t_toks	*new_node;
	int	item;
	
	item = 0;
	while (new_tokens[item])
	{
		new_node = ft_lstnew_toks(new_tokens[item]);
		if (!new_node)
		{
			ft_lstclear_toks(addition, free);
			return ;
		}
		add_token_info(new_node);
		ft_lstadd_back_toks(addition, new_node);
		item++;
	}
}

static void	add_commands(t_toks **addition, int lst_size)
{
	t_toks	*token;

	token = *addition;
	if (lst_size > 1)
		token->command = 0;
	else
		token->command = 1;
	token = token->next;
	while (token)
	{
		token->command = 1;
		token = token->next;
	}
}

static void	update_token_info(t_toks **addition, int delim, int lst_size)
{
	if (delim == '|')
		add_commands(addition, lst_size);
	//else if (delim == '<')
}

static void	add_to_tokens(t_toks **tokens, t_toks *token, t_toks **addition)
{
	t_toks	*tok;
	t_toks	*add;
	t_toks	*temp;
	t_toks	*next;
	t_toks	*last;

	tok = *tokens;
	add = *addition;
	next = NULL;
	while (tok->id != token->id - 1)
		tok = tok->next;
	temp = tok->next;
	if (temp->next != NULL)
		next = temp->next;
	tok->next = add;
	if (next != NULL)
	{
		last = ft_lstlast_toks(add);
		last->next = next;
	}
}

static void	split_by_delim(t_toks **tokens, t_toks *token, char delim)
{
	char	**new_tokens;
	t_toks	*addition;
	t_toks	*head;
	int	lst_size;

	new_tokens = ft_split(token->content, delim);
	if (!new_tokens)
		return ;
	addition = NULL;
	head = *tokens;
	lst_size = ft_lstsize_toks(head);
	build_list(&addition, new_tokens);
	free_array(new_tokens);
	update_token_info(&addition, delim, lst_size);
	if (lst_size > 1)
		add_to_tokens(tokens, token, &addition);
	else
		*tokens = addition;
	add_indexes(tokens);
}

void	eliminate_pipes(t_toks **tokens)
{
	t_toks	*token;

	token = *tokens;
	while (token)
	{
		if (struct_sum(token) != 1 && token->pipe == 1)
		{
			split_by_delim(tokens, token, '|');
			free(token->content);
			free(token);
			token = *tokens;
			identifier(tokens);
		}
		token = token->next;
	}
}
