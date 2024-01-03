#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("test1.txt", O_RDONLY);
	while (1)
	{
		gnl = get_next_line(fd);
		if (!gnl)
			break ;
		printf("%s", gnl);
		free(gnl);
	}
	close(fd);
	return (0);
}
