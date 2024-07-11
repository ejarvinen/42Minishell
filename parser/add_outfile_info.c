/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_outfile_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:06:28 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 11:59:43 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		to[i - 1] = -3;
	else
		to[i - 1] = -2;
}

static int	first_outfile(t_cmds **cmds, t_cmds *cmd, t_toks *token,
int append_flag)
{
	cmd->outfile_name = (char **)malloc(sizeof(char *) * 2);
	if (!cmd->outfile_name)
	{
		parser_error("malloc fail");
		ft_lstclear_pars(cmds);
		return (1);
	}
	if (copy_filenames(cmd->outfile_name, NULL, token->content, 0) > 0)
	{
		ft_lstclear_pars(cmds);
		return (1);
	}
	cmd->fd_outfile = (int *)malloc(sizeof(int) * 1);
	if (!cmd->fd_outfile)
	{
		parser_error("malloc fail");
		ft_lstclear_pars(cmds);
		return (1);
	}
	if (append_flag)
		cmd->fd_outfile[0] = -3;
	else
		cmd->fd_outfile[0] = -2;
	return (0);
}

static int	update_outfile_fds(t_cmds **cmds, t_cmds *cmd, int index, int append_flag)
{
	int		*fd_freeable;

	fd_freeable = cmd->fd_outfile;
	cmd->fd_outfile = (int *)malloc(sizeof(int) * index);
	if (!cmd->fd_outfile)
	{
		parser_error("malloc fail");
		ft_lstclear_pars(cmds);
		return (1);
	}
	copy_fds(cmd->fd_outfile, fd_freeable, index, append_flag);
	free(fd_freeable);
	return (0);
}

static int	update_existing_outfiles(t_cmds **cmds, t_cmds *cmd, t_toks *token,
int append_flag)
{
	char	**freeable;
	int		index;

	index = get_index(cmd->outfile_name);
	freeable = cmd->outfile_name;
	cmd->outfile_name = (char **)malloc(sizeof(char *) * (index + 2));
	if (!cmd->outfile_name)
	{
		ft_lstclear_pars(cmds);
		return (1);
	}
	if (copy_filenames(cmd->outfile_name, freeable, token->content, index) > 0)
	{
		ft_freearray(freeable);
		ft_lstclear_pars(cmds);
		return (1);
	}
	ft_freearray(freeable);
	if (update_outfile_fds(cmds, cmd, index + 1, append_flag) > 0)
		return (1);
	return (0);
}

/*
strdups outfile name and saves it to cmd; adds corresponding append
info according to given flag
*/
t_toks	*add_outfile_info(t_mini *shell, t_cmds *cmd, t_toks *token,
int append_flag)
{
	token = token->next;
	if (syntax_check(token, &shell->cmds, shell) > 0)
		return (NULL);
	if (cmd->outfile_name == NULL)
	{
		if (first_outfile(&shell->cmds, cmd, token, append_flag) > 0)
			return (NULL);
	}
	else
	{
		if (update_existing_outfiles(&shell->cmds, cmd, token, append_flag) > 0)
			return (NULL);
	}
	cmd->append = append_flag;
	return (token);
}
