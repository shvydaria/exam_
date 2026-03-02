#include <string.h>
#include <stdio.h>


void 	swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void	solve(char *str, int start, int end)
{
	if (start == end)
	{
		printf("%s\n", str);
		return ;
	}
	for (int i = start;i <= end;i++)
	{
		swap(&str[start], &str[i]);
		solve(str, start + 1, end);
		swap(&str[start], &str[i]);
	}
}
int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	int n = strlen(av[1]);
	solve(av[1], 0, n - 1);
	return 0;
}