#include <stdarg.h>
#include <unistd.h>
// i didnt get the scanf on the exam until now but
// try and fix scanf if you want, it still doenst work for me but it needs a couple more checks i think.
#define BUF 1024
#define SP(c) ((c)==' '||(c)=='\t'||(c)=='\n'||(c)=='\r'||(c)=='\f'||(c)=='\v')

static char b[BUF];
static int p, n;

static int next(void)
{
	if (p >= n)
	{
		n = read(0, b, BUF);
		p = 0;
		if (n <= 0)
			return -1;
	}
	return (unsigned char)b[p++];
}

static void unget(void)
{
	if (p > 0)
		p--;
}

static void skip_ws(void)
{
	int c;
	while ((c = next()) != -1 && SP(c)) {}
	if (c != -1)
		unget();
}

static int rd_c(char *o)
{
	int c = next();
	if (c == -1) return 0;
	*o = (char)c;
	return 1;
}

static int rd_d(int *o)
{
	int c, v = 0, ok = 0;
	skip_ws();
	while ((c = next()) >= '0' && c <= '9')
		v = v * 10 + (c - '0'); ok = 1;
	if (c != -1)
		unget();
	if (ok)
		*o = v;
	return ok;
}

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
