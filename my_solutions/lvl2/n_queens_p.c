#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int n;

void print_solution(int *queens) {
    int i = 0;
    while (i < n) {
        fprintf(stdout, "%d", queens[i]);
        if (i < n - 1)
            fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}

void solve(int col, int *queens, int *rows, int *diag1, int *diag2) {
    int r = 0;
    if (col == n) {
        print_solution(queens);
        return;
    }
    while (r < n) {
        if (rows[r] == 0 && diag1[r + col] == 0 && diag2[r - col + n - 1] == 0) {
            queens[col] = r;
            rows[r] = 1;
            diag1[r + col] = 1;
            diag2[r - col + n - 1] = 1;
            solve(col + 1, queens, rows, diag1, diag2);
            rows[r] = 0;
            diag1[r + col] = 0;
            diag2[r - col + n - 1] = 0;
        }
        r++;
    }
}

int main(int ac, char **av) {
    if (ac != 2)
        return (1);
    n = atoi(av[1]);
    if (n <= 0)
        return (1);
        
    int *queens = malloc(n * sizeof(int));
    int *rows = calloc(n, sizeof(int));
    int *diag1 = calloc((n * 2) - 1, sizeof(int));
    int *diag2 = calloc((n * 2) - 1, sizeof(int));
    solve(0, queens, rows, diag1, diag2);

    free(queens);
    free(rows);
    free(diag1);
    free(diag2);
    
    return (0);
}
