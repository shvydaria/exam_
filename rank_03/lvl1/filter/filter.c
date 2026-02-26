// Algorithm Overview:
// 1. Read input from stdin in chunks (BUFFER_SIZE)
// 2. Accumulate input in dynamically growing buffer
// 3. Find and replace all occurrences of search string with '*'
// 4. Print modified result

#define _GNU_SOURCE
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

int main(int ac, char **av)
{
	if (ac != 2)
		return 1; 
	char buffer[BUFFER_SIZE];
	char *temp;
}
