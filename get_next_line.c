/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:33:52 by pasha             #+#    #+#             */
/*   Updated: 2026/04/09 11:00:00 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *extract_line(char *static_buffer)
{
	char *line;
	size_t i;
	size_t j;

	if (!static_buffer || !static_buffer[0])
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (static_buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = static_buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char *remove_line(char *static_buffer)
{
	char *next;
	size_t i;
	size_t j;

	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (!static_buffer[i])
	{
		free(static_buffer);
		return (NULL);
	}
	i++;
	next = malloc(sizeof(char) * (ft_strlen(static_buffer + i) + 1));
	if (!next)
	{
		free(static_buffer);
		return (NULL);
	}
	j = 0;
	while (static_buffer[i])
		next[j++] = static_buffer[i++];
	next[j] = '\0';
	free(static_buffer);
	return (next);
}

static char *read_file(int fd, char *static_buffer)
{
	char *read_buffer;
	ssize_t bytes_read;

	bytes_read = 1;
	while (!(static_buffer && ft_strchr(static_buffer, '\n')) && bytes_read > 0)
	{
		read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!read_buffer)
		{
			free(static_buffer);
			return (NULL);
		}
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buffer);
			free(static_buffer);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			free(read_buffer);
			break;
		}
		read_buffer[bytes_read] = '\0';
		if (!static_buffer)
			static_buffer = read_buffer;
		else
			static_buffer = ft_strjoin_free(static_buffer, read_buffer);
		if (!static_buffer)
			return (NULL);
	}
	return (static_buffer);
}

char *get_next_line(int fd)
{
	static char *static_buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buffer = read_file(fd, static_buffer);
	if (!static_buffer || !static_buffer[0])
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	line = extract_line(static_buffer);
	if (!line)
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	static_buffer = remove_line(static_buffer);
	return (line);
}