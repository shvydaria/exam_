// #include "rip.h"
// #ifndef RIP_H
// # define RIP_H

// # include <stdio.h>

// void solve(char *str, int i, int l, int r, int bal);

// #endif

void solve(char *str, int i, int l, int r, int bal) {
    if (bal < 0)
        return;
    if (str[i] == '\0') {
        if (l == 0 && r == 0 && bal == 0)
            puts(str);
        return;
    }
    char c = str[i];

    if (c == '(' && l > 0) {
        str[i] = ' ';
        solve(str, i + 1, l - 1, r, bal);
        str[i] = c;
    } else if (c == ')' && r > 0) {
        str[i] = ' ';
        solve(str, i + 1, l, r - 1, bal);
        str[i] = c;
    }
    if (c == '(')
        solve(str, i + 1, l, r, bal + 1);
    else if (c == ')')
        solve(str, i + 1, l, r, bal - 1);
}

int main(int ac, char **av) {
    if (ac != 2)
        return (0);
    char str[2048];
    int i = 0;
    
    int l_remove = 0; 
    int r_remove = 0;

    while (av[1][i]) {
        str[i] = av[1][i];
        if (str[i] == '(') {
            l_remove++;
        } else if (str[i] == ')') {
            if (l_remove > 0)
                l_remove--;
            else
                r_remove++;
        }
        i++;
    }
    str[i] = '\0';
    solve(str, 0, l_remove, r_remove, 0);
    return (0);
}