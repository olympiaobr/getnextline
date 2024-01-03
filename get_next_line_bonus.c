/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olobresh <olobresh@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:38:29 by olobresh          #+#    #+#             */
/*   Updated: 2023/12/18 10:38:31 by olobresh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* Reads data from a file descriptor into a temporary storage buffer,
then merges this new data with any previously buffered text.
In case of read errors or reaching end-of-file,
it cleans up and updates buffered_text.*/
static int	buffer_data(int fd, char **buff_txt, char *tmp_stor)
{
	char	*mergd_txt;
	int		read_chrs;
	int		i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
		tmp_stor[i++] = '\0';
	read_chrs = read(fd, tmp_stor, BUFFER_SIZE);
	if (read_chrs <= 0)
	{
		if (read_chrs == -1)
		{
			if (*buff_txt)
			{
				free(*buff_txt);
				*buff_txt = NULL;
			}
		}
		return (read_chrs);
	}
	mergd_txt = ft_strjoin_and_free(*buff_txt, tmp_stor);
	if (!mergd_txt)
		return (-1);
	*buff_txt = mergd_txt;
	return (read_chrs);
}

/*Extracts next line from the buffered text,
then finds the newline character (if present) and calculates the len of the line.
then line gets extracted using substring
operation and any previously allocated line is freed first.*/
static void	extract_l(char **l, char **buff_txt)
{
	char	*nl_ptr;
	int		line_len;

	nl_ptr = ft_strchr(*buff_txt, '\n');
	if (nl_ptr != NULL)
	{
		line_len = nl_ptr - *buff_txt + 1;
	}
	else
	{
		line_len = ft_strlen(*buff_txt);
	}
	if (*l != NULL)
	{
		free(*l);
	}
	*l = ft_substr(*buff_txt, 0, line_len);
}

/*Resets the buffered text after a line is extracted;
finds the position of the newline character + creates new buff
starting from the character after the newline. old buff gets freed.
*/
static void	res_buff(char **buff_txt)
{
	char	*n_buff;
	char	*nl_ptr;

	nl_ptr = ft_strchr(*buff_txt, '\n');
	if (nl_ptr)
	{
		n_buff = ft_strdup(nl_ptr + 1);
		free(*buff_txt);
		*buff_txt = n_buff;
	}
	else
	{
		free(*buff_txt);
		*buff_txt = NULL;
	}
}

/*processes the buff text; if there's text in the buffer,
extract_l called to get the next line,
then calls res_buff to reset the buffer;
otherwise, it frees the buffer.
*/
char	*process_line(char **buff_txt, char *line)
{
	if (*buff_txt && **buff_txt)
	{
		extract_l(&line, buff_txt);
		res_buff(buff_txt);
	}
	else
	{
		free(*buff_txt);
		*buff_txt = NULL;
	}
	return (line);
}

/*main function to read the next line from a fd,
handles initial buffer setup, reads data using buffer_data,
and processes the buffered text to extract the next line.
*/
char	*get_next_line(int fd)
{
	static char	*buff_txt[FD_SETSIZE];
	char		*tmp_stor;
	char		*line;
	int			read_status;

	line = NULL;
	if (fd < 0 || fd >= FD_SETSIZE || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff_txt[fd])
		buff_txt[fd] = ft_strdup("");
	tmp_stor = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp_stor)
		return (NULL);
	while (!ft_strchr(buff_txt[fd], '\n'))
	{
		read_status = buffer_data(fd, &buff_txt[fd], tmp_stor);
		if (read_status <= 0)
			break ;
	}
	free(tmp_stor);
	line = process_line(&buff_txt[fd], NULL);
	return (line);
}
