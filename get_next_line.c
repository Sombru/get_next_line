/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pasha <pasha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 11:33:52 by pasha             #+#    #+#             */
/*   Updated: 2026/04/03 20:05:09 by pasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Concatenates the string src to the end of dest
char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

// delete line find
static char	*ft_next(char *static_buffer, int start)
{
	int		i;
	
		
	return (static_buffer);
}

// take line for return
static char	*ft_line(char *static_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!static_buffer[i])
		return (NULL);
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	line = malloc((i + 2)* sizeof(char));
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
	{
		line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] && static_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *static_buffer)
{
	char	*read_buffer;
	int		byte_read;

	if (!static_buffer)
		static_buffer = malloc(1);
	read_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	byte_read = 1;
	byte_read = read(fd, read_buffer, BUFFER_SIZE);
	if (byte_read <= 0)
	{
		return (NULL);
	}
	read_buffer[byte_read] = 0;
	static_buffer = malloc(sizeof(char) * (ft_strlen(static_buffer) + BUFFER_SIZE + 1));
	static_buffer = ft_strcat(static_buffer, read_buffer);
	free(read_buffer);
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (static_buffer && ft_strchr(static_buffer, '\n'))
			break;
		static_buffer = read_file(fd, static_buffer);
		if (!static_buffer)
			return (NULL);

	}	
	line = ft_line(static_buffer);
	// static_buffer = ft_next(static_buffer, ft_strlen(line));
	static_buffer = &static_buffer[ft_strlen(line)];
	// buff = line;
	// printf("bytes read: %d\n", bytes_read);
	// printf("buff: %s, line: %s\n", buff, line);
	return (line);
}