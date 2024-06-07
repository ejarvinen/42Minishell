/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_struct_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:24:07 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/07 12:05:44 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

t_cmds	*ft_lstnew_pars(int index)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds));
	if (new_node)
	{
		new_node->command = NULL;
		new_node->path = NULL;
		new_node->c_pid = -1;
		new_node->infile_name = NULL;
		new_node->outfile_name = NULL;
		new_node->heredoc = NULL;
		new_node->fd_infile = -1;
		new_node->fd_outfile = -1;
		new_node->id = index;
		new_node->commands = -1;
		new_node->builtin = -1;
		new_node->valid = -1;
		new_node->exit_status = -1;
		new_node->next = NULL;
		return (new_node);
	}
	perror("minishell");
	return (NULL);
}

/*
creates a new node with given input

t_cmds	*ft_lstnew_mini(char **cmd, char **paths, int index)
{
	t_cmds	*new_node;

	new_node = malloc(sizeof(t_cmds));
	if (new_node)
	{
		new_node->command = cmd;
		if (index == -1 || index == -3)
			new_node->path = ft_strdup("0");
		else if (index == -2)
			new_node->path = ft_strdup(cmd[0]);
		else
			new_node->path = full_path(paths[index], cmd[0]);
		if (!new_node->path)
		{
			free(new_node);
			return (NULL);
		}
		new_node->valid = index;
		new_node->next = NULL;
		return (new_node);
	}
	perror("pipex");
	return (NULL);
}*/

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
void	ft_lstclear_pars(t_cmds **lst, void (*del)(void*))
{
	t_cmds	*node;

	node = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		if (node->command)
			free_array(node->command);
		//(*del)(node->path);
		(*del)(node->infile_name);
		(*del)(node->outfile_name);
		(*del)(node->heredoc);
		free(node);
		node = *lst;
	}
	*lst = NULL;
}
