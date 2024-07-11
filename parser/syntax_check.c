/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:56:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/11 14:28:12 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
returns syntax error message for delimeters missing file info / heredoc
*/
int	syntax_check(t_toks *token, t_cmds **cmds, t_mini *shell)
{
	if (token == NULL)
	{
		parser_error("syntax error near unexpected token");
		shell->syntax = 1;
		if (cmds)
			ft_lstclear_pars(cmds);
		return (1);
	}
	return (0);
}

/*
checks if token or command list has ended prematurely and prints
the appropriate error message accordingly
*/
int	syntax_checker(t_cmds **cmds, t_cmds *cmd, t_toks *token, t_mini *shell)
{
	if (token == NULL)
	{
		parser_error("syntax error");
		shell->syntax = 1;
		ft_lstclear_pars(cmds);
		return (1);
	}
	else if (cmd == NULL && token != NULL)
	{
		syntax_check(NULL, cmds, shell);
		return (1);
	}
	else if (cmd == NULL)
		return (1);
	cmd->append = 0;
	return (0);
}
