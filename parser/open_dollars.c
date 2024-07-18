/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:27:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 15:24:29 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
copies contents from token to new_token and replaces key in tindex by key value
*/
static void	copy_contents(char *new_token, char *token, t_env *key, int tindex)
{
	int	index;
	int	key_index;

	index = 0;
	while (index < tindex)
	{
		new_token[index] = token[index];
		index++;
	}
	key_index = 0;
	while (key->value[key_index] != '\0')
	{
		new_token[index] = key->value[key_index];
		index++;
		key_index++;
	}
	tindex += (int)ft_strlen(key->key) + 1;
	while (token[tindex] != '\0')
	{
		new_token[index] = token[tindex];
		index++;
		tindex++;
	}
	new_token[index] = '\0';
}

/*
copies the contents of token to new_token skipping everything starting from
index start to index len
*/
static void	erase_dollar(char *new_token, char *token, int start, int len)
{
	int	index;
	int	tindex;

	index = 0;
	while (index < start)
	{
		new_token[index] = token[index];
		index++;
	}
	tindex = index + len;
	while (token[tindex] != '\0')
	{
		new_token[index] = token[tindex];
		index++;
		tindex++;
	}
	new_token[index] = '\0';
}

/*
mallocs space for new token string and copies the old token contents
and replacing the identified key with it's value
*/
static char	*expand_key(char *token, t_env *key, int len, int start)
{
	char	*new_token;

	new_token = (char *)malloc(sizeof(char)
			* (ft_strlen(token) - len + ft_strlen(key->value)));
	if (!new_token)
		return (NULL);
	copy_contents(new_token, token, key, start - 1);
	return (new_token);
}

/*
if key exists and it has a value, the value is inserted in the token where
key was found; otherwise erase dollar sign and key from token string
*/
static char	*expand(char *token, t_env **envs, int start, int len)
{
	char	*var;
	t_env	*key;
	char	*new_token;

	if (len > 0)
	{
		var = ft_substr(token, start, len);
		if (!var)
			return (NULL);
		key = key_finder(var, envs);
		free(var);
		if (key != NULL)
		{
			new_token = expand_key(token, key, len, start);
			return (new_token);
		}
	}
	new_token = (char *)malloc(sizeof(char) * (ft_strlen(token) - len));
	if (!new_token)
		return (NULL);
	erase_dollar(new_token, token, start - 1, len + 1);
	return (new_token);
}

/*
identifies key for dollar sign and expands it to it's value if value is given
*/
void	expand_dollar(t_mini *shell, t_toks **token, int *index, int in_doubles)
{
	int		varlen;
	char	*freeable;
	t_toks	*item;

	if (identify_exitcode(shell, token, index, in_doubles) > 0)
		return ;
	item = *token;
	varlen = identify_expandable(item->content + *index + 1);
	if ((varlen == 0 && in_doubles == 1)
		|| (varlen == 0 && in_doubles == 0 && item->content[*index + 1] == 0))
	{
		(*index)++;
		return ;
	}
	freeable = item->content;
	item->content = expand(item->content, &shell->env, *index + 1, varlen);
	if (!item->content)
	{
		*index = -1;
		return ;
	}
	free(freeable);
}
