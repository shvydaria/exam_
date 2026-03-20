#include "gnl_norm.h"

char *join_and_free(char *s1, char *s2) {
    int i = 0, j = 0;
    char *res;

    while (s1 && s1[i]) i++;
    while (s2 && s2[j]) j++;

    res = malloc(i + j + 1);
    if (!res) 
        return (NULL);

    i = 0;
    if (s1) {
        while (s1[i]) { 
            res[i] = s1[i]; 
            i++; 
        }
    }
    j = 0;
    while (s2[j]) {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    free(s1);
    return (res);
}

char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    int i = 0;
    int bytes = 1;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (buffer[0] == '\0') {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0)
            return (NULL);
        buffer[bytes] = '\0';
    }

    while (bytes > 0) {
        line = join_and_free(line, buffer);
        if (!line)
            return (NULL);
        i = 0;
        while (line[i] && line[i] != '\n')
            i++;

        if (line[i] == '\n') {
            int j = 0;
            i++;
            while (line[i]) {
                buffer[j++] = line[i];
                line[i++] = '\0';
            }
            buffer[j] = '\0';
            return (line);
        }
        
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0) { 
            free(line); 
            buffer[0] = '\0';
            return (NULL);
        }
        buffer[bytes] = '\0';
    }
    return (line);
}