#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char** argv)
{
	int fd = STDIN_FILENO;
	char buff[2048];
	if (argc != 1)
	{
		printf("opening: %s\n", argv[1]);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			printf("Error: could not open the file\n");
			return 1;
		}
		
	}
	printf("%s\n", get_next_line(fd));

}