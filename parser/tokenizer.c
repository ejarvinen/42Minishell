/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:36:05 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/18 14:04:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
looks for a closing quote in str according to type quote, returns -1 on error,
1 if matching quote is found and 0 if quote was not found
*/
static int	closing_quote(char const *str, int *index, int quote)
{
	while (str[*index] != quote && str[*index + 1] != '\0')
		(*index)++;
	if (str[*index + 1] == '\0' && str[*index] != quote)
		return (-1);
	else if (str[*index] == quote && (str[*index + 1] == '\0'
			|| str[*index + 1] == 32 || str[*index + 1] == 9))
		return (1);
	else
		return (0);
}

/*
find_token helper function to find the matching quote in str by quote_type
*/
static void	find_closing_quote(char *str, int *index, int quote_type)
{
	int	checker;
	
	(*index)++;
	checker = closing_quote(str, index, quote_type);
	while (checker == 0)
	{
		(*index)++;
		checker = closing_quote(str, index, quote_type);
	}
	(*index)++;
}

/*
finds a word in str that is either separated by beginning/end of string, space,
tab or one type of quote as long as there's a matching quote found in the string
*/
static int	find_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 39)
		find_closing_quote(str, &i, 39);
	else if (str[i] == 34)
		find_closing_quote(str, &i, 34);
	else
	{
		while (str[i] != 32 && str[i] != 9 && str[i] != 0)
		{
			if (str[i] == 39)
			{
				find_closing_quote(str, &i, 39);
				return (i);
			}
			else if (str[i] == 34)
			{
				find_closing_quote(str, &i, 34);
				return (i);
			}
			i++;
		}
	}
	return (i);
}

/*
finds the next token in leftovers and returns it, sets letfovers to point to
after the just found token
*/
static char	*empty_leftovers(char **leftovers)
{
	char	*lunchbox;
	char	*new;
	int		index;

	lunchbox = *leftovers;
	index = find_token(lunchbox);
	if (lunchbox[index] == '\0')
	{
		new = *leftovers;
		*leftovers = lunchbox + index;
		return (new);
	}
	lunchbox[index] = '\0';
	new = lunchbox;
	*leftovers = lunchbox + index + 1;
	return (new);
}

/*
tokenizes string str, returns the next token in str when called with NULL
*/
char	*ft_strtok(char *str)
{
	static char	*leftovers;
	int			index;

	if (!str || !*str)
	{
		if (ft_strlen(leftovers) == 0)
		{
			leftovers = NULL;
			return (NULL);
		}
		return (empty_leftovers(&leftovers));
	}
	index = find_token(str);
	if (str[index] == '\0')
	{
		leftovers = NULL;
		return (str);
	}
	leftovers = str + index + 1;
	str[index] = '\0';
	return (str);
}
