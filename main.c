#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	fd = STDIN_FILENO;
	if (argc > 1)
	{
		printf("opening: %s\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Error: could not open the file\n");
			return (1);
		}
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		printf("line[%d]. %s", i, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (fd != STDIN_FILENO)
		close(fd);
	return (0);
}
