/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:30 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/09 12:17:59 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_index(char **array)
{
	int	index;
	
	index = 0;
	if (!array)
		return (index);
	while (array[index])
	{
		index++;
	}
	return (index);
}

int	copy_filenames(char **to, char **from, char *new_file, int index)
{
	int	i;

	i = 0;
	if (from != NULL)
	{
		while (i < index)
		{
			to[i] = ft_strdup(from[i]);
			if (!to[i])
				return (1);
			i++;
		}
	}
	to[i] = ft_strdup(new_file);
	if (!to[i])
		return (1);
	to[i + 1] = NULL;
	return (0);
}

/*
strdups infile name and saves it to cmd; adds corresponding append info
*/
static t_toks	*add_infile_info(t_cmds **cmds, t_cmds *cmd, t_toks *token, int heredoc_flag)
{
	char	*freeable;
	int		prev_fd;
	
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	if (cmd->infile_name == NULL)
	{
		cmd->infile_name = ft_strdup(token->content);
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (heredoc_flag)
		{
			cmd->heredoc = ft_strdup(token->content);
			if (!cmd->heredoc)
			{
				ft_lstclear_pars(cmds);
				return (NULL);
			}
			cmd->fd_infile = 0;
		}
		else
		{
			cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
			if (cmd->fd_infile < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(cmd->infile_name);
			}
		}
	}
	else
	{
		freeable = cmd->infile_name;
		cmd->infile_name = ft_strdup(token->content);
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		free(freeable);
		if (heredoc_flag)
		{
			cmd->heredoc = ft_strdup(token->content);
			if (!cmd->heredoc)
			{
				ft_lstclear_pars(cmds);
				return (NULL);
			}
			if (cmd->fd_infile > 1)
				close(cmd->fd_infile);
			cmd->fd_infile = 0;
		}
		else
		{
			prev_fd = cmd->fd_infile;
			if (prev_fd > 1)
				close(prev_fd);
			cmd->fd_infile = open(cmd->infile_name, O_RDONLY, 0666);
			if (cmd->fd_infile < 0 && prev_fd != -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(cmd->infile_name);
			}
		}
	}
	return (token);
}

static void	copy_fds(int *to, int *from, int index, int append_flag)
{
	int	i;

	i = 0;
	while (i < index)
	{
		to[i] = from[i];
		i++;
	}
	if (append_flag)
		to[i] = -3;
	else
		to[i] = -2;
}

/*
strdups outfile name and saves it to cmd; adds corresponding append
info according to given flag
*/
static t_toks	*add_outfile_info(t_cmds **cmds, t_cmds *cmd,
	t_toks *token, int append_flag)
{
	char	**freeable;
	int		*fd_freeable;
	int	index;
	
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	if (cmd->outfile_name == NULL)
	{
		cmd->outfile_name = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->outfile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (copy_filenames(cmd->outfile_name, NULL, token->content, 0) > 0)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		cmd->fd_outfile = (int *)malloc(sizeof(int) * 1);
		if (!cmd->fd_outfile)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (append_flag)
			cmd->fd_outfile[0] = -3; // -3 for append
		else
			cmd->fd_outfile[0] = -2; //  -2 for trunc
	}
	else
	{
		index = get_index(cmd->outfile_name);
		freeable = cmd->outfile_name;
		cmd->outfile_name = (char **)malloc(sizeof(char *) * (index + 2));
		if (!cmd->outfile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (copy_filenames(cmd->outfile_name, freeable, token->content, index) > 0)
		{
			ft_freearray(freeable);
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		ft_freearray(freeable);
		fd_freeable = cmd->fd_outfile;
		cmd->fd_outfile = (int *)malloc(sizeof(int) * (index + 1));
		if (!cmd->fd_outfile)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		copy_fds(cmd->fd_outfile, fd_freeable, index, append_flag);
		free(fd_freeable);
	}
	cmd->append = append_flag;
	return (token);
}

/*
strdups a heredoc delimiter and saves it to cmd; adds corresponding append info
*/
/* static t_toks	*add_heredoc_info(t_cmds **cmds, t_cmds *cmd, t_toks *token)
{
	char	**freeable;
	int	index;
	
	token = token->next;
	if (syntax_check(token, cmds) > 0)
		return (NULL);
	if (cmd->infile_name == NULL)
	{
		cmd->infile_name = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (copy_filenames(cmd->infile_name, NULL, "heredoc", 0) > 0)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
	}
	else
	{
		index = get_index(cmd->infile_name);
		freeable = cmd->infile_name;
		cmd->infile_name = (char **)malloc(sizeof(char *) * (index + 2));
		if (!cmd->infile_name)
		{
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		if (copy_filenames(cmd->infile_name, freeable, "heredoc", index) > 0)
		{
			ft_freearray(freeable);
			ft_lstclear_pars(cmds);
			return (NULL);
		}
		ft_freearray(freeable);
	}
	cmd->heredoc = ft_strdup(token->content);
	if (!cmd->heredoc)
	{
		ft_lstclear_pars(cmds);
		return (NULL);
	}
	return (token);
} */

/*
if append is still uninitialized for a command, sets it's value to 0
*/
static t_toks	*append_checker(t_cmds *cmd, t_toks *token)
{
	if (cmd->append < 1)
		cmd->append = 0;
	token = token->next;
	return (token);
}

/*
loops through tokens and commands; adds filename, appends and heredoc delimeter
info to appropriate commands
*/
void	fill_redir_info(t_cmds **cmds, t_toks **tokens)
{
	t_toks	*token;
	t_cmds	*cmd;

	token = *tokens;
	cmd = *cmds;
	while (token && cmd)
	{
		if (token->id > 0 && token->pipe == 1 && struct_sum(token) == 1)
		{
			cmd = cmd->next;
			token = token->next;
			if (syntax_checker(cmds, cmd, token) > 0)
				return ;
		}
		else if (token->in_redir == 1 && struct_sum(token) == 1)
			token = add_infile_info(cmds, cmd, token, 0);
		else if (token->out_redir == 1 && struct_sum(token) == 1)
			token = add_outfile_info(cmds, cmd, token, 0);
		else if (token->append == 1 && struct_sum(token) == 1)
			token = add_outfile_info(cmds, cmd, token, 1);
		else if (token->heredoc_delimiter == 1 && struct_sum(token) == 1)
			token = add_infile_info(cmds, cmd, token, 1);
			//token = add_heredoc_info(cmds, cmd, token);
		else
			token = append_checker(cmd, token);
	}
}
