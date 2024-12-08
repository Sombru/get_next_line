/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura < pkostura@student.42prague.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:39:22 by pkostura          #+#    #+#             */
/*   Updated: 2024/02/06 12:57:34 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
// The strchr() function returns a pointer  to
// the  first occurrence of the character c in
// the string s.

char	*ft_strjoin(char *string, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!string)
	{
		string = (char *)malloc(1 * sizeof(char));
		string[0] = '\0';
	}
	if (!string || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(string) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (string)
		while (string[++i] != '\0')
			str[i] = string[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(string) + ft_strlen(buff)] = '\0';
	free(string);
	return (str);
}

char	*ft_get_line(char *string)
{
	int		i;
	char	*str;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		str[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_string(char *string)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(string) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (string[i])
		str[j++] = string[i++];
	str[j] = '\0';
	free(string);
	return (str);
}

// ---------
// GET_LINE
// ---------
// Extracts the line (ending in either line break and `\0` or only `\0` in EOF)
// from static string.
// PARAMETERS
// #1. The pointer to the static string from previous runs of get_next_line.
// RETURN VALUES
// The string with the full line ending in a line break (`\n`) + (`\0`).
// -------------
// NEW_string
// -------------
// Stores in the static string the new updated string with whatever
// is left from the original, minus the line extracted.
// PARAMETERS
// #1. The pointer to the static string from previous runs of get_next_line.
// RETURN VALUES
// The new updated string with whatever is left from the original static, minus
// line extracted.
