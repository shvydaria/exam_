#include <unistd.h>
#include <string.h>

// This struct is used to hold the counts of excess open and close parentheses.
typedef struct
{
    int open_exc;
    int close_exc;
} ExcessCounts;

// This function correctly calculates the minimum number of open and close
// parentheses that need to be removed to balance the string.
// Your original implementation was correct and remains unchanged.
ExcessCounts count_excess(char *s)
{
    int open = 0;
    int open_exc = 0;
    int close_exc = 0;

    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '(')
            open++;
        else if (s[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close_exc++;
        }
    }
    open_exc = open;
    return (ExcessCounts){open_exc, close_exc};
}

// The corrected recursive function to find all valid, balanced strings.
//
// Parameters:
// s: The input string being modified.
// pos: The current character position we are considering.
// len: The total length of the string.
// open_rem: The number of excess '(' we still need to remove.
// close_rem: The number of excess ')' we still need to remove.
// balance: The current balance of parentheses in the string being built.
//          A '(' increments it, and a ')' decrements it.
void solve(char *s, int pos, int len, int open_rem, int close_rem, int balance)
{
    // Base Case: If we have processed the whole string...
    if (pos == len)
    {
        // ...and the string is balanced (balance is 0), print the solution.
        if (balance == 0)
        {
            write(1, s, len);
            write(1, "\n", 1);
        }
        return;
    }

    if (s[pos] == '(')
    {
        // Option 1: Remove the '('.
        // If we still have excess open parentheses to remove,
        // we can explore this path.
        if (open_rem > 0)
        {
            s[pos] = ' '; // "Remove" it by replacing with a space.
            solve(s, pos + 1, len, open_rem - 1, close_rem, balance);
            s[pos] = '('; // Backtrack: restore the character for other recursive paths.
        }

        // Option 2: Keep the '('.
        // This is always a valid option to explore.
        // We increment the balance and continue.
        solve(s, pos + 1, len, open_rem, close_rem, balance + 1);
    }
    else if (s[pos] == ')')
    {
        // Option 1: Remove the ')'.
        // Similar to the '(', if we have excess to remove, explore this path.
        if (close_rem > 0)
        {
            s[pos] = ' '; // "Remove" it.
            solve(s, pos + 1, len, open_rem, close_rem - 1, balance);
            s[pos] = ')'; // Backtrack.
        }

        // Option 2: Keep the ')'.
        // We can only keep a ')' if the current balance is positive
        // (meaning there's an open '(' to match it with).
        if (balance > 0)
        {
            solve(s, pos + 1, len, open_rem, close_rem, balance - 1);
        }
    }
    else // If the character is not a parenthesis (e.g., a space from a previous removal).
    {
        // Just move to the next character.
        solve(s, pos + 1, len, open_rem, close_rem, balance);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        // A simple message for incorrect usage.
        write(2, "Usage: ./rip \"(()...)\"\n", 23);
        return 1;
    }

    // It's safer to work on a copy of the input string.
    char s[1024];
    strncpy(s, av[1], 1023);
    s[1023] = '\0';

    int len = 0;
    while (s[len])
        len++;

    ExcessCounts excess = count_excess(s);

    // Start the recursion from the beginning of the string (pos 0)
    // with an initial balance of 0.
    solve(s, 0, len, excess.open_exc, excess.close_exc, 0);

    return 0;
}

// ./rip "()())()()()()())()"

// it should always start with '('  even after spaces and end with ')'