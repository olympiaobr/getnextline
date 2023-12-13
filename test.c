#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main()
{
	int		fd;
	char	*nextline;

	fd = open("test", O_RDONLY);
	while (1)
	{
		nextline = get_next_line(fd);
		if (!nextline)
			break ;
		printf("%s", nextline);
		free(nextline);
	}
	close(fd);
	return (0);
}
