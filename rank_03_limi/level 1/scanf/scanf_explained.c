/*
// i didnt get the scanf on the exam until now but
// try and fix scanf if you want, it still doenst work for me but it needs a couple more checks i think.
 * SCANF (Explained)
 * Purpose: Minimal implementation of scanf for reading integers and characters from stdin.
 * Usage: ft_scanf(format, ...), where format supports %d (int) and %c (char).
 *
 * Key implementation details:
 * - Reads input from stdin using a static buffer for efficiency.
 * - Skips whitespace as needed.
 * - Handles %d (decimal integer) and %c (character) format specifiers.
 * - Uses variadic arguments to assign values to provided pointers.
 */

#include <stdarg.h>
#include <unistd.h>

#define BUF 1024
#define SP(c) ((c)==' '||(c)=='\t'||(c)=='\n'||(c)=='\r'||(c)=='\f'||(c)=='\v')

// Static buffer for efficient reading from stdin
static char b[BUF];
static int p, n;

// Reads the next character from stdin buffer, refilling if needed
static int next(void)
{
	if (p >= n)
	{
		n = read(0, b, BUF);
		p = 0;
		if (n <= 0)
			return -1; // End of input or error
	}
	return (unsigned char)b[p++];
}

// Moves the buffer pointer back by one (for lookahead/unget)
static void unget(void)
{
	if (p > 0)
		p--;
}

// Skips whitespace characters in the input
static void skip_ws(void)
{
	int c;
	while ((c = next()) != -1 && SP(c)) {}
	if (c != -1)
		unget();
}

// Reads a single character from input and stores it in *o
static int rd_c(char *o)
{
	int c = next();
	if (c == -1) return 0;
	*o = (char)c;
	return 1;
}

// Reads an integer from input and stores it in *o
static int rd_d(int *o)
{
	int c, v = 0, ok = 0;
	skip_ws(); // Skip leading whitespace
	while ((c = next()) >= '0' && c <= '9')
		v = v * 10 + (c - '0'), ok = 1;
	if (c != -1)
		unget(); // Put back non-digit
	if (ok)
		*o = v;
	return ok;
}

/*
 * ft_scanf:
 * Parses the format string and reads values from stdin accordingly.
 * Supports %d (int) and %c (char).
 * Returns the number of successfully assigned input items.
 */
int ft_scanf(const char *format, ...)
{
	va_list ap;
	int asg = 0;

	va_start(ap, format);
	while (*format)
	{
		if (SP(*format))
		{
			skip_ws();
			while (*format && SP(*format))
				format++;
			continue;
		}
		if (*format == '%' && format[1])
		{
			int ok = 0;
			format++;
			if (*format == 'd')
				ok = rd_d(va_arg(ap, int *));
			else if (*format == 'c')
				ok = rd_c(va_arg(ap, char *));
			if (!ok)
				break;
			asg++;
		}
		format++;
	}
	va_end(ap);
	return asg;
}

/*
Test cases for ft_scanf:

// Normal: read two integers
Input: "12 34\n"
Format: "%d %d"
Expected: 12, 34

// Normal: read integer and character
Input: "42 x\n"
Format: "%d %c"
Expected: 42, 'x'

// Edge: read character and integer
Input: "y 99\n"
Format: "%c %d"
Expected: 'y', 99

// Edge: input with extra whitespace
Input: "   7    8\n"
Format: "%d %d"
Expected: 7, 8

// Edge: input with no whitespace between numbers
Input: "56,78\n"
Format: "%d %d"
Expected: 56, 78

// Edge: input with invalid integer
Input: "abc 123\n"
Format: "%d %d"
Expected: fail on first %d

// Edge: input with only one value
Input: "5\n"
Format: "%d %d"
Expected: 5, fail on second %d

// Edge: negative integer
Input: "-42\n"
Format: "%d"
Expected: 0 (does not handle negative numbers)

// Edge: empty input
Input: ""
Format: "%d"
Expected: fail

// Edge: input with only whitespace
Input: "    "
Format: "%d"
Expected: fail

// Edge: input with special characters
Input: "@ #\n"
Format: "%c %c"
Expected: '@', '#'

// Edge: input with more values than format
Input: "1 2 3\n"
Format: "%d %d"
Expected: 1, 2 (3 ignored)

// Edge: input with fewer values than format
Input: "1\n"
Format: "%d %d"
Expected: 1, fail

// Edge: input with newline only
Input: "\n"
Format: "%d"
Expected: fail
*/
