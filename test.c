/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:33:35 by lodemetz          #+#    #+#             */
/*   Updated: 2023/11/25 13:54:02 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
