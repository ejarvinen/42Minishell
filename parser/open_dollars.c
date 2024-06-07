/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dollars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:27:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/05/30 13:47:02 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	identify_expandable(char *token)
{
	int	index;

	index = 0;
	while (token[index] != '\0' && token[index] != 34 && token[index] != 39 && token[index] != 32)
		index++;
	return (index);
}

static t_env	*find_key(char *var, t_env **envs)
{
	t_env	*env;
	size_t	var_len;

	env = *envs;
	var_len = ft_strlen(var);
	while (env)
	{
		if (var_len == ft_strlen(env->key) && ft_strncmp(var, env->key, var_len) == 0)
		{
			if (!env->value[0] || !env->value)
				return (NULL);
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

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
	tindex += (int)ft_strlen(key->key) + 2;
	while (token[tindex] != '\0')
	{
		new_token[index] = token[tindex];
		index++;
		tindex++;
	}
	new_token[index] = '\0';
}

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
		key = find_key(var, envs);
		free(var);
		if (key != NULL)
		{
			new_token = (char *)malloc(sizeof(char) * (ft_strlen(token) - len + ft_strlen(key->value)));
			if (!new_token)
				return (NULL);
			copy_contents(new_token, token, key, start - 1);
			return (new_token);
		}
	}
	new_token = (char *)malloc(sizeof(char) * (ft_strlen(token) - len));
	if (!new_token)
		return (NULL);
	erase_dollar(new_token, token, start - 1, len + 1);
	return (new_token);
}

void	expand_dollar(t_toks **token, t_env **envs, int *index, int in_doubles)
{
	int		varlen;
	int		new_len;
	char	*freeable;
	t_toks	*item;
	
	item = *token;
	varlen = identify_expandable(item->content + *index + 1);
	if (varlen == 0 && in_doubles == 1)
		return ;
	freeable = item->content;
	item->content = expand(item->content, envs, *index + 1, varlen);
	if (item->content == NULL)
	{
		*index = -1;
		return ;
	}
	new_len = (int)ft_strlen(item->content) - (int)ft_strlen(freeable);
	if (new_len > 0)
		*index += new_len;
	free(freeable);
}
