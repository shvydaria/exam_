#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	char buffer[BUFFER_SIZE];
	char *temp;
	char *res = NULL;
	char *pos;
	char *find = av[1];
	int res_size = 0;
	int find_size = strlen(av[1]);
	int bytes;

	while ((bytes = read(0, buffer, BUFFER_SIZE)))
	{
		temp = realloc(res, bytes + res_size + 1);
		if (!temp)
			return (free(res), 1);
		res = temp;
		memmove(res + res_size, buffer, bytes);
		res_size += bytes;
		res[res_size] = 0;
	}

	if (bytes < 0)
		return (free(res), 1);
	if (!res)
		return (free(res), 1);

	while ((pos = memmem(res, res_size, find, find_size)))
	{
		for (int i = 0; i < find_size; i++)
			pos[i] = '*';
	}
	printf("%s", res);
	free(res);
	return (0);
}