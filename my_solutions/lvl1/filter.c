#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);

	char buffer[1024];
	char *res = NULL;
	char *find = av[1];
	char *temp;
	char *pos;
	int find_len = strlen(find);
	int res_size = 0;
	int bytes;

	while ((bytes = read(0, buffer, sizeof(buffer))) > 0)
	{
		temp = realloc(res, res_size + bytes + 1);
		if (!temp)
		{
			free(res);
			perror("Error");
			return (1);
		}
		res = temp;
		memmove(res + res_size, buffer, bytes);
		res_size += bytes;
		res[res_size] = '\0';
	}

	if (bytes < 0)
	{
		free(res);
		perror("Error");
		return (1);
	}
	if (!res)
		return (0);

	while ((pos = memmem(res, res_size, find, find_len))) {
		for (int i = 0; i < find_len; i++)
			pos[i] = '*';
	}
	write(1, res, res_size);
	free(res);
	return (0);
}

// in case of infinite loop:
/*
char *search_start = res;
int remaining_size = res_size;
while ((pos = memmem(search_start, remaining_size, find, find_len))) {
    for (int i = 0; i < find_len; i++)
        pos[i] = '*';
    search_start = pos + find_len;
    remaining_size = res_size - (search_start - res);
}
*/