/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:20:00 by pasha             #+#    #+#             */
/*   Updated: 2026/05/08 14:24:14 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *static_buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

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

static char	*remove_line(char *static_buffer)
{
	char	*next;
	size_t	i;
	size_t	j;

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

static char	*read_file(int fd, char *static_buffer)
{
	char	*read_buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!(static_buffer && ft_strchr(static_buffer, '\n')) && bytes_read > 0)
	{
		read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!read_buffer)
			return (free(static_buffer), NULL);
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buffer), free(static_buffer), NULL);
		read_buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			return (free(read_buffer), static_buffer);
		if (!static_buffer)
			static_buffer = read_buffer;
		else
			static_buffer = ft_strjoin_free(static_buffer, read_buffer);
		if (!static_buffer)
			return (NULL);
	}
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	static_buffer[fd] = read_file(fd, static_buffer[fd]);
	if (!static_buffer[fd] || !static_buffer[fd][0])
	{
		free(static_buffer[fd]);
		static_buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(static_buffer[fd]);
	if (!line)
	{
		free(static_buffer[fd]);
		static_buffer[fd] = NULL;
		return (NULL);
	}
	static_buffer[fd] = remove_line(static_buffer[fd]);
	return (line);
}

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include "get_next_line.h"

// int main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = STDIN_FILENO;
// 	if (argc > 1)
// 	{
// 		printf("opening: %s\n", argv[1]);
// 		fd = open(argv[1], O_RDONLY);
// 		if (fd == -1)
// 		{
// 			printf("Error: could not open the file\n");
// 			return (1);
// 		}
// 	}
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("line[%d]. %s", i, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	if (fd != STDIN_FILENO)
// 		close(fd);
// 	return (0);
// }