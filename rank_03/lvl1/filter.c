#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	// Check for exactly 1 non-empty argument
	if (ac != 2 || av[1][0] == '\0')
		return (1);

	char buffer[1024]; // Standard buffer size
	char *res = NULL;
	char *temp;
	char *find = av[1];
	char *pos;
	int find_len = strlen(find);
	int res_size = 0;
	int bytes;

	// 1. READ Loop
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

	// 2. FILTER Loop
	while ((pos = memmem(res, res_size, find, find_len))) {
		for (int i = 0; i < find_len; i++)
			pos[i] = '*';
	}
	// 3. OUTPUT
	write(1, res, res_size);
	free(res);
	return (0);
}