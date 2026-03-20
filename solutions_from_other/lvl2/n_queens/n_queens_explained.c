#include <stdlib.h>
#include <stdio.h>

// Global variables to store the board size and the board state
int n, *board;

/*
 * Checks if placing a queen at (row, col) is safe.
 * We check for three conflicts:
 * 1. Same row: another queen already placed in the same row.
 * 2. Same major diagonal: difference between row and col is the same.
 * 3. Same minor diagonal: sum of row and col is the same.
 */
int is_safe(int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		// Check if another queen is in the same row or diagonals
		if (board[i] == row ||
			board[i] - i == row - col ||
			board[i] + i == row + col)
			return 0; // Not safe
	}
	return 1; // Safe to place queen
}

/*
 * Recursive function to try placing queens column by column.
 * - col: the current column to place a queen in.
 *
 * The recursion works as follows:
 * - For each row in the current column, check if it's safe to place a queen.
 * - If safe, place the queen and recursively try to solve for the next column.
 * - If we reach col == n, it means we've placed all queens successfully, so we print the solution.
 * - This approach explores all possible placements (backtracking).
 */
void solve(int col)
{
	int row;
	if (col == n)
	{
		// All queens placed, print the solution
		for (row = 0; row < n; row++)
		{
			printf("%d", board[row]);
			if (row < n - 1)
				printf(" ");
		}
		printf("\n");
		return;
	}
	// Try placing a queen in every row of the current column
	for (row = 0; row < n; row++)
	{
		if (is_safe(row, col))
		{
			board[col] = row; // Place queen
			solve(col + 1);   // Recurse to next column
			// No need to "remove" queen explicitly; next iteration will overwrite board[col]
		}
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 0;

	n = atoi(av[1]);
	if (n <= 0)
		return 1;

	board = malloc(n * sizeof(int));
	if (!board)
		return 1;

	solve(0); // Start solving from the first column
	free(board);
	return 0;
}

/*
Test cases for n_queens_explained:

// Normal: 4 queens (classic)
./n_queens_explained 4

// Normal: 5 queens
./n_queens_explained 5

// Normal: 8 queens (classic)
./n_queens_explained 8

// Edge: 1 queen (trivial)
./n_queens_explained 1

// Edge: 2 queens (no solution)
./n_queens_explained 2

// Edge: 3 queens (no solution)
./n_queens_explained 3

// Edge: 0 queens (invalid)
./n_queens_explained 0

// Edge: negative number (invalid)
./n_queens_explained -5

// Edge: large n (stress test, may be slow)
./n_queens_explained 10

// Edge: non-integer input (should error or ignore)
./n_queens_explained a

// Edge: missing argument (should error)
./n_queens_explained

// Edge: very large n (should handle gracefully or error)
./n_queens_explained 20
*/
