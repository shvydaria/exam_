#include <stdio.h>
#include <stdlib.h>

void print_basket(int *basket, int basket_len) {
    int i = 0;
    while (i < basket_len) {
        printf("%d", basket[i]);
        if (i < basket_len - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

void solve_powerset(int *input, int *basket, int size, int target, int pos, int sum, int basket_len) {
    if (pos == size) {
        if (sum == target)
            print_basket(basket, basket_len);
        return;
    }
    solve_powerset(input, basket, size, target, pos + 1, sum, basket_len);
    basket[basket_len] = input[pos];
    solve_powerset(input, basket, size, target, pos + 1, sum + input[pos], basket_len + 1);
}

int main(int ac, char **av) {
    if (ac < 3)
        return (1);

    int target = atoi(av[1]);
    int size = ac - 2;
    
    if (size < 0)
        size = 0;

    int *input = malloc(size * sizeof(int));
    int *basket = malloc(size * sizeof(int));

    if (!input || !basket)
        return (1); 

    int i = 0;
    while (i < size) {
        input[i] = atoi(av[i + 2]);
        i++;
    }
    
    solve_powerset(input, basket, size, target, 0, 0, 0);
    
    free(input);
    free(basket);
    return (0);
}


// void ft_putchar(char c) {
//     write(1, &c, 1);
// }

// void ft_putnbr(int n) {
//     if (n == -2147483648) {
//         write(1, "-2147483648", 11);
//         return;
//     }
//     if (n < 0) {
//         ft_putchar('-');
//         n = -n;
//     }
//     if (n > 9)
//         ft_putnbr(n / 10);
//     ft_putchar((n % 10) + '0');
// }

// int ft_atoi(const char *str) {
//     int i = 0, sign = 1, res = 0;
//     while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32) i++;
//     if (str[i] == '-' || str[i] == '+') {
//         if (str[i] == '-') sign = -1;
//         i++;
//     }
//     while (str[i] >= '0' && str[i] <= '9') {
//         res = (res * 10) + (str[i] - '0');
//         i++;
//     }
//     return (res * sign);
// }
