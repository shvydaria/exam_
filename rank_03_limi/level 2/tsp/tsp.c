#include <stdio.h>
#include <math.h>

float x[11], y[11];
int n, used[11];
float min_dist = 1e9;


float dist(int i, int j)
{
	return sqrtf((x[i] - x[j])*(x[i] - x[j])+(y[i]- y[j])*(y[i]- y[j]));
}

void	solve(int pos, int count, float cost)
{
	if (count == n)
	{
		cost += dist(pos, 0);
		if(cost < min_dist)
			min_dist = cost;
	}
	for(int i = 0;i < n;i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			solve(i, count + 1, cost + dist(pos, i));
			used[i] = 0;
		}
	}
}

int main(void)
{
	n = 0;
	while (n < 11 && scanf("%f, %f", &x[n], &y[n]) == 2)
		n++;

	used[0] = 1;
	solve(0, 1, 0);
	printf("%.2f\n", min_dist);
	return 0;
}
