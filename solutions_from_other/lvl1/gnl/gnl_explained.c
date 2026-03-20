#include "gnl_norm.h"
// Includes function prototypes and necessary macros/constants (like BUFFER_SIZE).

char *ft_strchr(char *s, int c)
{
    int i = 0; // Initialize index for string traversal.
    if (!s)
        return NULL; // Return NULL if input string is NULL.
    while (s[i] && s[i] != c)
        i++; // Loop until end of string or character 'c' is found.
    if (s[i] == c)
        return s + i; // Return pointer to first occurrence of 'c'.
    return NULL; // Return NULL if 'c' not found.
}
// Custom implementation of strchr: finds first occurrence of a character in a string.



void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0; // Index for copying bytes.
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i]; // Copy each byte from src to dest.
        i++;
    }
    return dest; // Return destination pointer.
}
// Custom memcpy: copies n bytes from src to dest.


ssize_t ft_strlen(char *s)
{
    ssize_t len = 0; // Counter for string length.
    while (s[len]) len++; // Increment until null terminator.
    return len; // Return length.
}
// Custom strlen: calculates length of a string.

int str_append_mem(char **s1, char *s2, size_t size2)
{
    if (!s1||!s2)
        return 0; // Return 0 if either pointer is NULL.
    size_t size1;
    if (*s1)
        size1 = ft_strlen(*s1); // Get length of first string if it exists.
    else
        size1 = 0;
    char *tmp = malloc(size2 + size1 + 1); // Allocate memory for combined string.
    if (!tmp)
        return 0; // Return 0 if allocation fails.
    if (*s1)
        ft_memcpy(tmp, *s1, size1); // Copy first string if it exists.
    ft_memcpy(tmp + size1, s2, size2); // Append second string (or memory block).
    tmp[size1 + size2] = 0; // Null-terminate the new string.
    free(*s1); // Free old string memory.
    *s1 = tmp; // Update pointer to new string.
    return 1; // Success.
}
// Appends a memory block (not necessarily a string) to a string, reallocating as needed.

int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2)); // Append s2 as a string to s1.
}
// Helper: appends a string to another string.


void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    if (dest > src)
    {
        i = n;
        while (i > 0)
        {
            i--;
            ((char *)dest)[i] = ((char *)src)[i]; // Copy backwards to handle overlap.
        }
    }
    if (dest < src)
        return ft_memcpy(dest, src, n); // Safe to copy forwards.
    return dest;
}
// Custom memmove: safely copies memory, even if regions overlap.


char *get_next_line(int fd)
{
    static char	buffer[BUFFER_SIZE + 1] = ""; // Persistent buffer for leftover data.
    char		*res = malloc(1); // Result string, initially empty.
    char        *tmp; // Temporary pointer for newline search.
    int read_ret;

    if (fd < 0 || !res)
        return free(res), NULL; // Return NULL if fd invalid or malloc fails.
    res[0] = 0; // Initialize result as empty string.
    while (1)
    {
        tmp = ft_strchr(buffer, '\n'); // Search for newline in buffer.
        if (tmp)
        {
            if(!str_append_mem(&res, buffer, tmp - buffer + 1))
                return free(res), NULL; // Append up to and including newline.
            ft_memmove(buffer, tmp + 1, ft_strlen(tmp + 1) +1); // Shift leftover buffer.
            return res; // Return line.
        }
        if (ft_strlen(buffer) > 0)
        {
            if (!str_append_str(&res, buffer))
                return free(res), NULL; // Append buffer to result.
            buffer[0] = 0; // Clear buffer.
        }
        read_ret = read(fd, buffer, BUFFER_SIZE); // Read more data from file.
        if (read_ret == -1)
            return free(res), NULL; // Error reading file.
        if (read_ret == 0)
        {
            if (ft_strlen(res) == 0)
                return free(res), NULL; // End of file and nothing to return.
            return res; // Return last line (no newline at end).
        }
        buffer[read_ret] = 0; // Null-terminate buffer.
    }
}
// Reads a line from fd, handling partial reads and buffering across calls.

int main(void)
{
    int fd = open("gnl.c", O_RDONLY, 0777); // Open file for reading.
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line); // Print each line as returned.
        free(line); // Free memory for each line.
    }
    return 0;
}
// Opens "gnl.c", prints each line using get_next_line, and frees memory.

/*
Test cases for get_next_line:

// Normal: file with several lines
File: test.txt
Content:
Hello
World
123

// Edge: file with one very long line (longer than BUFFER_SIZE)
File: longline.txt
Content: (a single line of 1000 'a's)

// Edge: file with empty lines
File: emptylines.txt
Content:
<empty line>
abc
<empty line>
def

// Edge: file with only one line, no newline at end
File: single_no_nl.txt
Content: HelloWorld

// Edge: file with only newlines
File: only_newlines.txt
Content:
<newline>
<newline>
<newline>

// Edge: file with no content (empty file)
File: empty.txt
Content: (empty)

// Edge: file with lines of varying length
File: mixed.txt
Content:
a
bb
ccc
dddd

// Edge: file with non-ASCII characters
File: unicode.txt
Content: åß∂ƒ©

-- Usage:
Compile and run, changing the filename in main() as needed.
*/