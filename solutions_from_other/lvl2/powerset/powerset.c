#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calc(int *sub, int sub_size)
{
	int sum = 0;
	for(int i = 0;i < sub_size;i++)
		sum += sub[i];
	return sum;

}

void	print(int *sub, int sub_size)
{
	for(int i = 0;i < sub_size;i++)
	{
		printf("%d", sub[i]);
		if(i < sub_size - 1)
			printf(" ");
	}
	printf("\n");

}

void	generate(int *arr, int target, int size, int index, int *sub, int sub_size)
{
	if(calc(sub, sub_size) == target)
		print(sub,sub_size);

	for(int i = index; i < size;i++)
	{
		sub[sub_size] = arr[i];
		generate(arr, target, size, i + 1, sub, sub_size + 1);
	}
}


int main(int ac, char **av)
{
	int arr[1000] = {0};
	int sub[1000] = {0};

	int target = atoi(av[1]);
	int size = ac - 2;

	for(int i = 2;i < ac;i++)
		arr[i - 2] = atoi(av[i]);

	generate(arr,target,size,0,sub,0);
	return 0;
}