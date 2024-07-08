/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 06:53:44 by emansoor          #+#    #+#             */
/*   Updated: 2024/07/08 13:32:02 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*trim_line(char *from, char *to)
{
	int	index;
	int	i;

	index = 0;
	while (from[index] != '\n' && index <= BUFFER_SIZE)
		index++;
	index++;
	i = 0;
	while (from[index] != '\0')
	{
		to[i] = from[index];
		i++;
		index++;
	}
	to[i] = '\0';
	return (0);
}

static char	*line_fetch(char *buff, int length)
{
	int		index;
	char	*line;

	line = (char *)malloc(sizeof(char) * length + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (index < length)
	{
		if (buff[index] == 10)
		{
			line[index] = buff[index];
			break ;
		}
		line[index] = buff[index];
		index++;
	}
	line[index + 1] = '\0';
	return (line);
}

static char	*content_sorter(char *buff, char *line, int terminator)
{
	char	*trashcan;

	buff[terminator] = '\0';
	trashcan = line;
	line = ft_strjoin(line, buff);
	free(trashcan);
	if (!line)
		return (NULL);
	if (newline_finder(line, ft_strlen(line)))
	{
		trim_line(buff, buff);
		trashcan = line;
		line = line_fetch(line, ft_strlen(line) - ft_strlen(buff));
		free(trashcan);
		if (!line)
			return (NULL);
		if (!buff[0] && !*line)
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
	ft_bzero(buff, BUFFER_SIZE + 1);
	return (line);
}

static char	*line_handler(int fd, char *buff, char *line)
{
	int	bytes_read;

	while (ft_strlen(buff) > 0)
	{
		line = content_sorter(buff, line, BUFFER_SIZE);
		if (!line)
			return (NULL);
		if (newline_finder(line, ft_strlen(line)))
			return (line);
	}
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line = content_sorter(buff, line, bytes_read);
		if (!line)
			return (NULL);
		if (newline_finder(line, ft_strlen(line)))
			return (line);
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	if (*line && !bytes_read)
		return (line);
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	line = line_handler(fd, buff, line);
	if (!line || !*line)
	{
		free(line);
		ft_bzero(buff, BUFFER_SIZE + 1);
		return (NULL);
	}
	return (line);
}
