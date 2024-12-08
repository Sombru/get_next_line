/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:40:51 by pkostura          #+#    #+#             */
/*   Updated: 2024/02/06 12:58:10 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

char	*ft_read_to_string(int fd, char *string)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(string, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		string = ft_strjoin(string, buff);
	}
	free(buff);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string = ft_read_to_string(fd, string);
	if (!string)
		return (NULL);
	line = ft_get_line(string);
	string = ft_new_string(string);
	return (line);
}

// NOTES
// fd vaue is negative when referring to invalid file
// read funtion returns 0 if is was sucsefull
// and -1 of not (the file cant be read)
// -------------
// GET_NEXT_LINE
// -------------
// DESCRIPTION
// This function takes an opened file descriptor and returns its next line.
// PARAMETERS
// #1. A file descriptor 
// RETURN VALUES
// If successful, get_next_line returns a string with the full line ending
// in a line break (`\n`) when there is one. 
// If an error occurs, or there's nothing more to read, it returns NULL.
// ------------------------------------------------------------------------
// READ_TO_STRING
// -----------------
// DESCRIPTION
// Takes the opened file descriptor and saves on a "buff" variable what read
// from it. Then joins it to the into static variable
// of the information.
// PARAMETERS
// #1. A file descriptor.
// #2. The pointer to the static string from previous runs of
// get_next_line.
// RETURN VALUES
// The new static string value with buffer joined of the info,
// or NULL if error.
