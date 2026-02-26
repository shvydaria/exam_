
#include "gnl_norm.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	if (!s)
		return NULL;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
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
	while (s[len]) len++;
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


	if (dest > src)
    {
		i = n;
		while (i > 0)
		{
        	i--;
        	((char *)dest)[i] = ((char *)src)[i];
		}
    }
    if (dest < src)
        return ft_memcpy(dest, src, n);
    return dest;
}

char *get_next_line(int fd)
{
    static char	buffer[BUFFER_SIZE + 1] = "";
    char		*res = malloc(1);
    char        *tmp;
	int read_ret;

	if (fd < 0 || !res)
		return free(res), NULL;
	res[0] = 0;
    while (1)
    {
		tmp = ft_strchr(buffer, '\n');
		if (tmp)
		{
			if(!str_append_mem(&res, buffer, tmp - buffer + 1))
				return free(res), NULL;
			ft_memmove(buffer, tmp + 1, ft_strlen(tmp + 1) +1);
			return res;
		}
		if (ft_strlen(buffer) > 0)
		{
			if (!str_append_str(&res, buffer))
				return free(res), NULL;
			buffer[0] = 0;
		}
		read_ret = read(fd, buffer, BUFFER_SIZE);
		if (read_ret == -1)
			return free(res), NULL;
		if (read_ret == 0)
		{
			if (ft_strlen(res) == 0)
				return free(res), NULL;
			return res;
		}
		buffer[read_ret] = 0;
	}
}

int main(void)
{
	int fd = open("gnl.c", O_RDONLY, 0777);
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return 0;
}