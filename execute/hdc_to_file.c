/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdc_to_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:20:14 by sataskin          #+#    #+#             */
/*   Updated: 2024/07/17 14:50:20 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	delimiter(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	if (c == '\n' || c == '\0')
		return (1);
	return (0);
}

static int	write_env(char *str, int i, t_env *env, int fd)
{
	t_env	*temp;
	int		index;

	index = i;
	while (delimiter(str[i]) == 0)
		i++;
	temp = hdoc_key(str, index, env);
	if (!temp)
		return (i);
	ft_putstr_fd(temp->value, fd);
	return (i);
}

void	heredoc_typer(t_env *env, char *str, int fd)
{
	int	i;
	
	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			i = write_env(str, i, env, fd);
		else
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}
