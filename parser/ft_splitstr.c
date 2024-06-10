/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:22:26 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/10 10:36:54 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**null_arr(void)
{
	char	**ptr;

	ptr = (char **)malloc(sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr[0] = NULL;
	return (ptr);
}

static char	**free_substrs(char **str, int nbr_of_subs)
{
	while (nbr_of_subs >= 0)
	{
		free(str[nbr_of_subs]);
		nbr_of_subs--;
	}
	free(str);
	return (NULL);
}

static char	**split_str(char **ptr, char const *s, char *c, int substrs)
{
	size_t	index;
	int		nbr_of_subs;
	int		start_index;
	size_t	slen;

	index = 0;
	nbr_of_subs = 0;
	start_index = 0;
	slen = ft_strlen(s);
	while (nbr_of_subs < substrs)
	{
		if (index < slen && ft_strncmp((s + index), c, 2) != 0)
		{
			start_index = index;
			while (ft_strncmp((s + index), c, 2) != 0 && index < slen)
				index++;
			ptr[nbr_of_subs] = ft_substr(s, start_index, index - start_index);
			if (!ptr[nbr_of_subs])
				return (free_substrs(ptr, nbr_of_subs));
			nbr_of_subs++;
		}
		index += 2;
	}
	ptr[nbr_of_subs] = 0;
	return (ptr);
}

static int	word_count(char const *s, size_t slen, char *c)
{
	size_t	index;
	int		substrs;

	index = 0;
	substrs = 0;
	while (index < slen)
	{
		if (ft_strncmp((s + index), c, 2) != 0 && (s[index + 1] == '\0' || ft_strncmp((s + index + 1), c, 2) == 0))
		{	
			substrs++;
			index++;
		}
		index++;
	}
	return (substrs);
}

char	**ft_splitstr(char const *s, char *c)
{
	char	**ptr;
	int		substrs;
	size_t	slen;

	slen = ft_strlen(s);
	if (!s || !slen)
		return (null_arr());
	substrs = word_count(s, slen, c);
	if (substrs)
	{
		ptr = (char **)malloc(sizeof(char *) * (substrs + 1));
		if (!ptr)
			return (NULL);
		return (split_str(ptr, s, c, substrs));
	}
	return (null_arr());
}
