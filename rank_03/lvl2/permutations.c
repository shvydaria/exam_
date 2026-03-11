// alphabetical order

#include <stdlib.h>
#include <unistd.h>

// 1. Simple strlen
int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

// 2. Simple bubble sort for alphabetical order
void sort_str(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        for (int j = i + 1; s[j]; j++)
        {
            if (s[i] > s[j])
            {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

void solve(char *s, char *res, int *used, int pos, int len)
{
    if (pos == len)
    {
        write(1, res, len);
        write(1, "\n", 1);
        return;
    }
    
    for (int i = 0; i < len; i++)
    {
        if (!used[i]) // If we haven't used this letter yet
        {
            used[i] = 1;
            res[pos] = s[i];
            solve(s, res, used, pos + 1, len);
            used[i] = 0; // Backtrack!
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 0;

    char *s = av[1];
    int len = ft_strlen(s);
    
    sort_str(s); // Sort it first!
    
    char *res = malloc(len + 1);
    int *used = calloc(len, sizeof(int)); // calloc sets everything to 0
    
    if (res && used)
        solve(s, res, used, 0, len);
        
    free(res);
    free(used);
    return 0;
}