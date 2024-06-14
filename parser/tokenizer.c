/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:36:05 by emansoor          #+#    #+#             */
/*   Updated: 2024/06/14 15:33:37 by emansoor         ###   ########.fr       */
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
	else if (str[*index] == quote && (str[*index + 1] == '\0' || str[*index + 1] == 32 || str[*index + 1] == 9))
		return (1);
	else
		return (0);
}

/*
find_token helper function to find the matching quote in str by quote_type
*/
static void	find_closing_quote(char *str, int *index, int quote_type)
{
	(*index)++;
	while (closing_quote(str, index, quote_type) == 0)
		(*index)++;
}

/*
finds a word in str that is either separated by beginning/end of string, space,
tab or one type of quote as long as there's a matching quote found in the string
*/
static int	find_token(char *str)
{
	int	index;
	
	index = 0;
	if (str[index] == 39)
		find_closing_quote(str, &index, 39);
	else if (str[index] == 34)
		find_closing_quote(str, &index, 34);
	else
	{
		while (str[index + 1] != 32 && str[index + 1] != 9 && str[index + 1] != 0)
		{
			if (str[index] == 39)
			{
				find_closing_quote(str, &index, 39);
				return (index);
			}
			else if (str[index] == 34)
			{
				find_closing_quote(str, &index, 34);
				return (index);
			}
			index++;
		}
	}
	return (index);
}

/*
tokenizes string str, returns the next token in str when called with NULL
*/
char	*ft_strtok(char *str)
{
	static char	*leftovers;
	char	*new;
	int	index;

	if (!str || !*str)
	{
		if (ft_strlen(leftovers) == 0)
			return (NULL);
		index = find_token(leftovers);
		new = leftovers;
		if (leftovers[index + 1] == '\0')
		{
			leftovers = leftovers + index + 1;
			return (new);
		}
		leftovers[index + 1] = '\0';
		leftovers = leftovers + index + 2;
		return (new);
	}
	index = find_token(str);
	if (str[index + 1] == '\0')
		return (str);
	leftovers = str + index + 2;
	str[index + 1] = '\0';
	return (str);
}
