/*
 * FILTER PROGRAM (Explained)
 * Purpose: Replace all occurrences of a search string with '*' characters in stdin input.
 * Usage: ./filter_explained <search_string>
 *
 * How it works:
 * 1. Reads input from stdin in chunks (BUFFER_SIZE).
 * 2. Dynamically accumulates the input into a buffer.
 * 3. Searches for all occurrences of the search string and replaces them with '*'.
 * 4. Prints the modified result.
 *
 * Key implementation details:
 * - Uses realloc to handle arbitrary input sizes.
 * - Uses memmem for efficient substring search.
 * - Handles memory and read errors.
 */

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
		return 1; // Expect exactly one argument (the search string)

	char buffer[BUFFER_SIZE]; // Temporary buffer for reading input
	char *temp;
	char *res = NULL;        // Pointer to dynamically growing result buffer
	char *pos;
	char *find = av[1];      // The search string to filter
	int res_size = 0;        // Current size of the result buffer
	int find_size = strlen(av[1]); // Length of the search string
	int bytes;

	// Read input from stdin in chunks
	while ((bytes = read(0, buffer, BUFFER_SIZE)))
	{
		// Expand the result buffer to fit new data
		temp = realloc(res, bytes + res_size + 1);
		if (!temp)
			return free(res), 1; // Memory allocation failed
		res = temp;
		// Copy new data to the end of the result buffer
		memmove(res + res_size, buffer, bytes);
		res_size += bytes;
		res[res_size] = 0; // Null-terminate for safety
	}

	if (bytes < 0)
		return free(res), 1; // Read error
	if (!res)
		return free(res), 1; // No input read

	// Search for all occurrences of the search string and replace with '*'
	while ((pos = memmem(res, res_size, find, find_size)))
	{
		// Replace each character of the found substring with '*'
		for (int i = 0; i < find_size; i++)
			pos[i] = '*';
		// Continue searching for next occurrence
	}

	// Output the filtered result
	printf("%s", res);
	free(res);
	return 0;
}

/*
Test cases for filter_explained:

// Normal: replace a word
Input: "hello world"
Arg: "world"
Expected: "hello *****"

// Normal: replace multiple occurrences
Input: "foo bar foo"
Arg: "foo"
Expected: "*** bar ***"

// Edge: search string not present
Input: "abcdef"
Arg: "xyz"
Expected: "abcdef"

// Edge: search string is empty
Input: "abc"
Arg: ""
Expected: "abc"

// Edge: input is empty
Input: ""
Arg: "a"
Expected: ""

// Edge: search string is a single character
Input: "banana"
Arg: "a"
Expected: "b*n*n*"

// Edge: search string is longer than input
Input: "hi"
Arg: "hello"
Expected: "hi"

// Edge: search string is the entire input
Input: "test"
Arg: "test"
Expected: "****"

// Edge: overlapping matches
Input: "aaaa"
Arg: "aa"
Expected: "**aa" or "****" (depends on memmem behavior)

// Edge: input with special characters
Input: "a$#a$#"
Arg: "$#"
Expected: "a**a**"

// Edge: input with whitespace
Input: "a b c d"
Arg: " "
Expected: "a*b*c*d"

// Edge: input with newlines
Input: "a\nb\nc"
Arg: "\n"
Expected: "a*b*c"

// Edge: large input (stress test)
Input: (10000 'a's)
Arg: "a"
Expected: (10000 '*')

// Edge: search string at start and end
Input: "abcabc"
Arg: "abc"
Expected: "***abc" then "******"

// Edge: search string is non-ASCII
Input: "åß∂åß∂"
Arg: "ß"
Expected: "å*∂å*∂"
*/
