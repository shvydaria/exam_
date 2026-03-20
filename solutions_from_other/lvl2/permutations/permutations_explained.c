/*
 * PERMUTATIONS (Explained)
 * Purpose: Print all permutations of a given string.
 * Usage: ./permutations_explained <string>
 *
 * Key implementation details:
 * - Uses recursion and backtracking to generate all possible orderings.
 * - Swaps characters in place to avoid extra memory usage.
 * - After each recursive call, swaps back to restore the original string (backtracking).
 */

#include <string.h>
#include <stdio.h>

// Swaps the values at two character pointers
void swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Recursively generates all permutations of the string.
 * - str: the string to permute
 * - start: the current index to fix
 * - end: the last index of the string
 *
 * The recursion works as follows:
 * - For each position from start to end, swap the current start with i.
 * - Recursively permute the rest of the string (start + 1 to end).
 * - After recursion, swap back to restore the original order (backtracking).
 * - When start == end, a full permutation is formed and printed.
 */
void solve(char *str, int start, int end)
{
	if (start == end)
	{
		printf("%s\n", str);
		return;
	}
	for (int i = start; i <= end; i++)
	{
		swap(&str[start], &str[i]);      // Place i-th char at start
		solve(str, start + 1, end);      // Recurse for the rest
		swap(&str[start], &str[i]);      // Backtrack: restore original order
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	int n = strlen(av[1]);
	solve(av[1], 0, n - 1);
	return 0;
}

/*
Test cases for permutations_explained:

// Normal: three distinct characters
./permutations_explained abc

// Normal: four distinct characters
./permutations_explained abcd

// Edge: single character
./permutations_explained a

// Edge: two characters, same
./permutations_explained aa

// Edge: three characters, some duplicates
./permutations_explained aba

// Edge: empty string (should not print anything)
./permutations_explained ""

// Edge: string with spaces
./permutations_explained "a b"

// Edge: string with special characters
./permutations_explained "a$#"

// Edge: string with numbers
./permutations_explained "123"

// Edge: long string (stress test)
./permutations_explained abcdef

// Edge: string with all identical characters
./permutations_explained "zzz"

// Edge: string with mixed case
./permutations_explained "AbC"

// Edge: string with non-printable characters (should handle gracefully)
./permutations_explained "\n\t"

// Edge: string with Unicode (if supported by environment)
./permutations_explained "åß∂"
*/
