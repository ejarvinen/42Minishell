/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:24:07 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/10 16:54:02 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
adds a new node to list of cmds
*/
t_cmds	*ft_lstnew_pars(int index)
{
	t_cmds	*new_node;

	new_node = (t_cmds *)malloc(sizeof(t_cmds));
	if (new_node)
	{
		new_node->command = NULL;
		new_node->path = NULL;
		new_node->c_pid = -1;
		new_node->infile_name = NULL;
		new_node->outfile_name = NULL;
		new_node->heredoc = NULL;
		new_node->fd_infile = -1;
		new_node->fd_outfile = NULL;
		new_node->id = index;
		new_node->commands = -1;
		new_node->builtin = -1;
		new_node->valid = -1;
		new_node->append = -1;
		new_node->exit_status = -1;
		new_node->next = NULL;
		return (new_node);
	}
	parser_error("malloc fail");
	return (NULL);
}

/*
returns the number of nodes in lst
*/
int	ft_lstsize_pars(t_cmds *lst)
{
	int	nodes;

	nodes = 0;
	while (lst)
	{
		lst = lst->next;
		nodes++;
	}
	return (nodes);
}

/*
returns the last node in lst
*/
t_cmds	*ft_lstlast_pars(t_cmds *lst)
{
	t_cmds	*temp;

	if (lst)
	{
		temp = lst;
		while (temp->next)
			temp = temp->next;
		return (temp);
	}
	return (NULL);
}

/*
adds node new in the back of the list lst
*/
void	ft_lstadd_back_pars(t_cmds **lst, t_cmds *new)
{
	t_cmds	*last;

	if (new)
	{
		if (*lst)
		{
			last = ft_lstlast_pars(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

/*
frees a linked list
*/
void	ft_lstclear_pars(t_cmds **lst)
{
	t_cmds	*node;

	node = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		if (node->command)
			ft_freearray(node->command);
		if (node->path)
			free(node->path);
		if (node->infile_name)
			free(node->infile_name);
		if (node->outfile_name)
			ft_freearray(node->outfile_name);
		if (node->fd_outfile)
			free(node->fd_outfile);
		if (node->heredoc)
			free(node->heredoc);
		free(node);
		node = *lst;
	}
	*lst = NULL;
}
