#include "gnl_norm.h"

char *ft_strchr(char *s, int c)
{
    if(!s)
        return NULL;
    int i = 0;
    while(s[i] != c && s[i])
        i++;
    if (s[i] == c)
        return s + i;
    else
        return NULL;
}
void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}
ssize_t ft_strlen(char *s)
{
	ssize_t len = 0;
	while (s[len])
        len++;
	return len;
}
int str_append_mem(char **s1, char *s2, size_t size2)
{
	if (!s1||!s2)
		return 0;
	size_t size1;
	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
        return 0;
	if (*s1)
    	ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = 0;
    free(*s1);
    *s1 = tmp;
    return 1;
}
int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i = 0;

    if(!dest || !src)
        return(NULL);
	if (dest > src)
    {
		i = n;
		while (i > 0)
		{
            ((char *)dest)[i] = ((char *)src)[i];
        	i--;
		}
    }
    if (dest < src)
        return ft_memcpy(dest, src, n);
    return dest;
}

char *get_next_line(int fd)
{
    static char	buffer[BUFFER_SIZE + 1] = "";
    char *ret = malloc(1);
    char        *pos;
	int bytes;

    if (fd < 0 || !ret)
		return free(ret), NULL;  
    if (ret)
        ret[0] = '\0';
    while(1)
    {
        pos = ft_strchr(buffer, '\n');
        if (pos) {
            if(!str_append_mem(&ret, buffer, pos - buffer + 1))
				return free(ret), NULL;
			size_t leftover_len = ft_strlen(pos + 1);
            ft_memmove(buffer, pos + 1, leftover_len);
            buffer[leftover_len] = '\0';
			return ret;
        }
        if (ft_strlen(buffer) > 0)
		{
			if (!str_append_str(&ret, buffer))
				return free(ret), NULL;
			buffer[0] = 0;
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return free(ret), NULL;
		if (bytes == 0)
		{
			if (ft_strlen(ret) == 0)
				return free(ret), NULL;
			return ret;
		}
		buffer[bytes] = 0;
    }
}