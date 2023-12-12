#include "get_next_line.h"

// Reads and buffers data from file descriptor.
static int buffer_data(int fd, char **buffered_text, char *temp_storage)
{
    char *merged_text;
    int read_chars;
    int i;

    i = 0;
    while (i < BUFFER_SIZE + 1)
        temp_storage[i++] = '\0';
    read_chars = read(fd, temp_storage, BUFFER_SIZE);
    if (read_chars <= 0)
    {
        if (read_chars == -1)
        {
            if (*buffered_text)
            {
                free(*buffered_text);
                *buffered_text = NULL;
            }
        }
        return read_chars;
    }
    merged_text = ft_strjoin_and_free(*buffered_text, temp_storage);
    if (!merged_text)
        return (-1);
    *buffered_text = merged_text;
    return read_chars;
}

// Extracts the next line from buffered text.
static void extract_line(char **line, char **buffered_text)
{
    char *newline_ptr;
    int line_length;

    newline_ptr = ft_strchr(*buffered_text, '\n');
    if (newline_ptr != NULL)
    {
        line_length = newline_ptr - *buffered_text + 1;
    }
    else
    {
        line_length = ft_strlen(*buffered_text);
    }
    if (*line != NULL)
    {
        free(*line);
    }
    *line = ft_substr(*buffered_text, 0, line_length);
}

// Resets buffer for the next read.
static void reset_buffer(char **buffered_text)
{
    char *new_buffer;
    char *newline_ptr;

    newline_ptr = ft_strchr(*buffered_text, '\n');
    if (newline_ptr)
    {
        new_buffer = ft_strdup(newline_ptr + 1);
        free(*buffered_text);
        *buffered_text = new_buffer;
    }
    else
    {
        free(*buffered_text);
        *buffered_text = NULL;
    }
}

char *process_line(char **buffered_text, char *line)
{
    if (*buffered_text && **buffered_text)
    {
        extract_line(&line, buffered_text);
        reset_buffer(buffered_text);
    }
    else
    {
        free(*buffered_text);
        *buffered_text = NULL;
    }
    return line;
}

// Main function to get the next line from file descriptor.
char *get_next_line(int fd)
{
    static char *buffered_text = NULL;
    char *temp_storage;
    char *line;
    int read_status;

    line = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    if (!buffered_text)
        buffered_text = ft_strdup("");
    temp_storage = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!temp_storage)
        return NULL;
    while (!ft_strchr(buffered_text, '\n'))
    {
        read_status = buffer_data(fd, &buffered_text, temp_storage);
        if (read_status <= 0) break;
    }
    free(temp_storage);
    return process_line(&buffered_text, line);
}
