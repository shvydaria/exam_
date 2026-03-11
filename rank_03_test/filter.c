#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

int main (int ac, char **av) {
    if (ac != 2 || av[1][0] == '\0')
        return (1);

    char buffer[BUFFER_SIZE];
    char *res = NULL;
    char *find = av[1];
    char *pos;
    char *temp;
    int bytes;
    int find_length = strlen(find);
    int res_size = 0;

    while((bytes = read(0, buffer, sizeof(buffer))) > 0) {
        temp = realloc(res, res_size + bytes + 1);
        if(!temp) {
            free(res);
            perror("E");
            return(1);
        }
        res = temp;
        memmove(res+res_size, buffer, bytes);
        res_size += bytes;
        res[res_size];
    }

    if(bytes < 0) {
        free(res);
        perror("Error");
        return(1);
    }
    if(!res) {
        free(res);
        return(0);
    }

    while((pos = memmem(res, res_size, find, find_length))) {
        for(int i = 0; i < find_length; i++)
            pos[i] = '*';
    }

    write(1, res, res_size);
    free(res);
    return (0);

}
