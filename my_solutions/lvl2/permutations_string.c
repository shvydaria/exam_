#include <stdlib.h>
#include <unistd.h>

void putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(char *str) {
    int i = 0;

    while(str[i]){
        putchar(str[i]);
        i++;
    }
}

int ft_strlen(char *str) {
    int length = 0;
    while(str[length]) {
        length++;
    }
    return(length);
}

void sort_string(char *str) {
    int i = 0;
    int j;
    int len = ft_strlen(str);

    while (i < len - 1) {
        j = i + 1;
        while (j < len) {
            if (str[i] > str[j]) {
                char tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void solve_string(char *str, char *res, int *used, int pos, int len) {
    int i = 0;

    if(pos == len) {
        res[len] = '\0';
        ft_putstr(res);
        putchar('\n');
        return;
    }
    while(i < len) {
        if(used[i] == 0) {
            used[i] = 1;
            res[pos] = str[i];
            solve_string(str, res, used, pos + 1, len);
            used[i] = 0;
        }
        i++;
    }
}

int main(int ac, char **av) {
    int len = 0;
    int i = 0;

    if(ac != 2)
        return(1);

    len = ft_strlen(av[1]);
    sort_string(av[1]);

    char *res = malloc((len + 1)*sizeof(char));
    int *used = malloc(len*sizeof(int));
    
    while (i < len) {
        used[i] = 0;
        i++;
    }
    solve_string(av[1], res, used, 0, len);
    free(res);
    free(used);
    return(0);
}

