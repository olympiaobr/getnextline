#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	int		fd_two;
	int		index;
	char	*gnl;

	fd = open("test1.txt", O_RDONLY);
	fd_two = open("test2.txt", O_RDONLY);
	index = 9;
	while (index--)
	{
		gnl = get_next_line(fd);
		if (gnl)
			printf("%s", gnl);
		else
			printf("%s", "NULL");
		free(gnl);
		gnl = get_next_line(fd_two);
		if (gnl)
			printf("%s", gnl);
		else
			printf("%s", gnl);
		free(gnl);
	}
	close(fd);
}
