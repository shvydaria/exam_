
#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 2 || av[1][0] == '\0')
        return 1;

    char    *res = NULL;
    char    *tmp;
    char    buf[42];
    int     size = 0;
    int     len = strlen(av[1]);
    int     bytes;

    while ((bytes = read(0, buf, 42)))
    {
        tmp = realloc(res, size + bytes + 1);
        if (!tmp)
            return perror("Error: "), free(res), 1;
        res = tmp;
        memmove(res + size, buf, bytes);
        size += bytes;
        res[size] = 0;
    }
    if (bytes < 0)
        return perror("Error: "), free(res), 1;
    if (!res)
        return 0;

    char *cur = res;
    char *pos;

    pos = memmem(cur, size - (cur - res), av[1], len);
    while (pos)
    {
        memset(pos, '*', len);
        cur = pos + len;
        pos = memmem(cur, size - (cur - res), av[1], len);
    }
    printf("%s", res);
    free(res);
    return 0;
}