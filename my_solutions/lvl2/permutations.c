#include <stdlib.h>
#include <unistd.h>

int n;

int	atoi(const char *str) {
    int i = 0;
    int sign = 1;
    int res = 0;

    while((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if(str[i] == '-') {
        sign = -1;
        i++;
    }
    else if(str[i] == '+')
        i++;
    while(str[i] >= '0' && str[i] <= '9') {
        res = (res*10) + (str[i] - '0');
        i++;
    }
    return(res * sign);
}

void swap(int *a, int *b) {
    int x;
    x = *a;
    *a = *b;
    *b = x;
}

void putchar(char c) {
    write(1, &c, 1);
}

void putnbr (int n) {
    char c;

    if(n > 9)
        putnbr(n/10);
    c = (n%10) + '0';
    putchar(c);
}

void print_arr(int *arr) {
    int i = 0;

    while(i < n) {
        putnbr(arr[i]);
        if (i < n - 1)
            putchar(' ');
        i++;
    }
    write(1, "\n", 1);
}

void solve(int pos, int *arr) {
    int i;
    if (pos == n) {
        print_arr(arr);
        return;
    }
    i = pos;
    while(i < n) {
        swap(&arr[pos], &arr[i]);
        solve(pos+1, arr);
        swap(&arr[pos], &arr[i]);
        i++;
    }
}

int main(int ac, char **av) {
    if(ac != 2)
        return(0);
    
    n = atoi(av[1]);

    if(n <= 0)
        return(1);
    else if(n == 1) {
        write(1, "1\n", 2);
        return (0);
    }

    int *arr = malloc(n*sizeof(int));
    
    int i = 0;
    while(i < n) {
        arr[i] = i+1;
        i++;
    }
    solve(0, arr);
    free(arr);
    return (0);
}

// NEGATIVE VERSION
// void putnbr(int n) {
//     if (n == -2147483648) {
//         write(1, "-2147483648", 11);
//         return;
//     }
//     if (n < 0) {
//         putchar('-');
//         n = -n;
//     }
//     if (n > 9) {
//         putnbr(n / 10);
//     }
//     putchar((n % 10) + '0');
// }