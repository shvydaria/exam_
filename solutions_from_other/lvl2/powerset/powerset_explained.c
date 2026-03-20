/*
 * POWERSET (Explained)
 * Purpose: Print all subsets of an array whose sum equals a target value.
 * Usage: ./powerset_explained <target> <num1> <num2> ... <numN>
 *
 * Key implementation details:
 * - Uses recursion to generate all possible subsets (the powerset).
 * - At each step, either include the current element or skip it.
 * - When a subset's sum matches the target, print it.
 * - Uses an auxiliary array to store the current subset.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Calculates the sum of the current subset
int calc(int *sub, int sub_size)
{
	int sum = 0;
	for (int i = 0; i < sub_size; i++)
		sum += sub[i];
	return sum;
}

// Prints the current subset
void print(int *sub, int sub_size)
{
	for (int i = 0; i < sub_size; i++)
	{
		printf("%d", sub[i]);
		if (i < sub_size - 1)
			printf(" ");
	}
	printf("\n");
}

/*
 * Recursively generates all subsets of arr[].
 * - arr: input array
 * - target: target sum to match
 * - size: total number of elements in arr
 * - index: current index in arr to consider
 * - sub: array holding the current subset
 * - sub_size: number of elements in sub
 *
 * The recursion works as follows:
 * - If the sum of the current subset equals target, print it.
 * - For each element from index to end:
 *     - Add arr[i] to the current subset.
 *     - Recurse to generate further subsets including arr[i].
 *     - (No need to explicitly remove arr[i]; sub_size is incremented/decremented by recursion.)
 */
void generate(int *arr, int target, int size, int index, int *sub, int sub_size)
{
	if (calc(sub, sub_size) == target)
		print(sub, sub_size);

	for (int i = index; i < size; i++)
	{
		sub[sub_size] = arr[i];
		generate(arr, target, size, i + 1, sub, sub_size + 1);
	}
}

int main(int ac, char **av)
{
	int arr[1000] = {0};
	int sub[1000] = {0};

	if (ac < 3)
		return 1;

	int target = atoi(av[1]);
	int size = ac - 2;

	for (int i = 2; i < ac; i++)
		arr[i - 2] = atoi(av[i]);

	generate(arr, target, size, 0, sub, 0);
	return 0;
}

/*
Test cases for powerset_explained:

// Normal: positive numbers, target sum exists
./powerset_explained 5 1 2 3 4

// Normal: negative numbers, target sum exists
./powerset_explained -3 -1 -2 -3 4

// Normal: mix of positive and negative, multiple solutions
./powerset_explained 0 1 -1 2 -2 3 -3

// Edge: target sum is 0, array contains 0
./powerset_explained 0 0 1 2

// Edge: target sum is 0, array does not contain 0
./powerset_explained 0 1 2 3

// Edge: single element equals target
./powerset_explained 7 7

// Edge: single element does not equal target
./powerset_explained 5 7

// Edge: all elements are the same, target is sum of all
./powerset_explained 6 2 2 2

// Edge: all elements are zero, target is zero
./powerset_explained 0 0 0 0

// Edge: negative target, positive numbers
./powerset_explained -5 1 2 3 4

// Edge: negative target, negative numbers
./powerset_explained -6 -1 -2 -3

// Edge: empty input (should not print anything)
./powerset_explained 0

// Edge: large input (stress test)
./powerset_explained 10 1 2 3 4 5 6 7 8 9 10

// Edge: duplicate numbers
./powerset_explained 4 2 2 2

// Edge: target sum not possible
./powerset_explained 100 1 2 3

// Edge: input with non-integer values (should ignore or error)
./powerset_explained 5 1 a 2

// Edge: negative and positive, target is negative
./powerset_explained -1 1 -2 3 -2

// Edge: only one number, not matching target
./powerset_explained 2 1

// Edge: only one number, matching target
./powerset_explained 1 1
*/
