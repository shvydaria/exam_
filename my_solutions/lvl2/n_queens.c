#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int n;

void    ft_putchar(char c) {
	write(1, &c, 1);
}

int	atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

void print_board(int *queens) {
	int row = 0;
	int col;

	while (row < n) {
		col = 0;
		while (col < n) {
			if (queens[col] == row) {
				ft_putchar('Q');
			} else {
				ft_putchar('.');
			}
			col++;
		}
		write(1, "\n", 1); 
		row++;
	}
}

int	solve(int col, int *queens, int *rows, int *diag1, int *diag2)
{
	int	r = 0;
	
	if (col == n)
	{
		print_board(queens);
		return (1);
	}
	while (r < n)
	{
		if (rows[r] == 0 && diag1[r + col] == 0 && diag2[r - col + n - 1] == 0)
		{
			queens[col] = r;
			rows[r] = 1;
			diag1[r + col] = 1;
			diag2[r - col + n - 1] = 1;
			if (solve(col + 1, queens, rows, diag1, diag2) == 1)
				return (1);
			rows[r] = 0;
			diag1[r + col] = 0;
			diag2[r - col + n - 1] = 0;
		}
		r++;
	}
	return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (0);

    n = atoi(av[1]);
    if (n <= 0)
        return (1);
        
    int *queens = malloc(n * sizeof(int));
    int *rows = calloc(n, sizeof(int));
    int *diag1 = calloc((n * 2) - 1, sizeof(int));
    int *diag2 = calloc((n * 2) - 1, sizeof(int));

    if (solve(0, queens, rows, diag1, diag2) == 0)
        write(1, "No solution\n", 12);

    free(queens); free(rows); free(diag1); free(diag2);
    return (0);
}

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (0);

// 	int i;

// 	n = atoi(av[1]);
// 	if (n <= 0)
// 		return (1);
// 	int *queens = malloc(n * sizeof(int));
// 	int *rows = malloc(n * sizeof(int));
// 	int *diag1 = malloc(((n * 2) - 1) * sizeof(int));
// 	int *diag2 = malloc(((n * 2) - 1) * sizeof(int));
// 	i = 0;
// 	while (i < n)
// 	{
// 		queens[i] = 0;
// 		rows[i] = 0;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < ((n * 2) - 1))
// 	{
// 		diag1[i] = 0;
// 		diag2[i] = 0;
// 		i++;
// 	}
//     if (solve(0, queens, rows, diag1, diag2) == 0) {
//         write(1, "No solution\n", 12);
//     }
// 	free(queens);
// 	free(rows);
// 	free(diag1);
// 	free(diag2);
// 	return (0);
// }
