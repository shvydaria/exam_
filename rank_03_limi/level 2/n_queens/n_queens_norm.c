#include <stdlib.h>
#include <stdio.h>

int n, *board;


int is_safe(int row, int col)
{
	for(int i = 0; i< col;i++)
	{
		if (board[i] == row ||
			board[i] - i == row - col ||
			board[i] + i == row + col)
			return 0;
	}
	return 1;
}

void	solve(int col)
{
	int row;
	if (col == n)
	{
		for (row = 0;row < n;row++)
		{
			printf("%d", board[row]);
			if(row < n - 1)
				printf(" ");
		}
		printf("\n");
		return ;
	}
	for (row = 0;row < n;row++)
	{
		if(is_safe(row, col))
		{
			board[col] = row;
			solve(col + 1);
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

	solve (0);
	free(board);
	return 0;
}