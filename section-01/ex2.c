#include <stdio.h>
#include <stdlib.h>

void fizzbuzz(int *n);

int main()
{
	int *numbers = malloc(20 * sizeof(int));
	for (int x = 1; x <= 20; x++)
	{
		numbers[x] = x;
	} 

	for (int y = 1; y <= 20; y++)
	{
		fizzbuzz(&numbers[y]);	
	}

	printf("\n");

	for (int z = 1; z <= 30; z++)
	{
		int temp = z;
		fizzbuzz(&temp);	
	}
	
}

void fizzbuzz(int *n)
{

	if (*n % 3 == 0 && *n % 5 == 0)
	{
		printf("%d ", *n);
		printf("FizzBuzz\n");	
		printf("\n");
	}	

	else if (*n % 3 == 0)
	{
		printf("%d ", *n);
		printf("Fizz\n");
		printf("\n");
	}

	else if (*n % 5 == 0)
	{
		printf("%d ", *n);
		printf("Buzz\n");
		printf("\n");
	}
	
	else
	{
		printf("");
	}
}
