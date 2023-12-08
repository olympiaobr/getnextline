#include "get_next_line.h"

char *read_line(int fd, char **static_buf)
{
    char    buf[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char    *temp;

    bytes_read = read(fd, buf, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buf[bytes_read] = '\0';
        if (!*static_buf)
            *static_buf = ft_strdup("");
        temp = ft_strdup(*static_buf);
        free(*static_buf);
        *static_buf = ft_strjoin_free(&temp, &buf);
        if (ft_strchr(buf, '\n'))
            break;
        bytes_read = read(fd, buf, BUFFER_SIZE);
    }
    if (bytes_read < 0)
        return NULL;
    return *static_buf;
}

char *extract_line(char **static_buffer)
{

}

void update_buffer(char **static_buffer)
{

}

char *get_next_line(int fd) {
    static char *static_buffer = NULL;
    char *line;

    line = read_line(fd, &static_buffer);
    if (!line)
        return NULL;
    line = extract_line(&static_buffer);
    update_buffer(&static_buffer);

    return line;
}
