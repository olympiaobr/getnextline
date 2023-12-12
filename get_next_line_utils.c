#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	return (l);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char *ft_strdup(const char *s)
{
    char *dup;
    size_t i;

    dup = malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (s[i]) {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

char *ft_strjoin_and_free(char *s1, char *s2)
{
    char *new_str;
    size_t i, j;

    new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!new_str)
    {
        free(s1);  // Free the old string to prevent leaks
        return (NULL);
    }
    i = -1;
    j = 0;
    while (s1[++i] != '\0')
        new_str[j++] = s1[i];
    i = -1;
    while (s2[++i] != '\0')
        new_str[j++] = s2[i];
    new_str[j] = '\0';
    free(s1);  // Free the old string after copying
    return (new_str);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *substr;
    size_t  i;
    size_t  s_len;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    if (start >= s_len)
        return (malloc(sizeof(char) * 2));
    if (len > s_len - start)
        len = s_len - start;
    substr = (char *)malloc(sizeof(char) * (len + 1));
    if (!substr)
        return (NULL);
    i = 0;
    while (i < len)
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    return (substr);
}
