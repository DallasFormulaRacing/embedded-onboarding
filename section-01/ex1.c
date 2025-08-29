#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void fizzbuzz(int *n);
int comparator(const void *x_void, const void *y_void);


int main()
{
	printf("\n");
	printf("Hello, World!\n");
	printf("\n");
	int a = 2;
	int b = 3;
	swap(&a, &b);
	printf("\n");	
			
        int *numbers = malloc(20 * sizeof(int));
	int length = 20;
	
        
	for (int x = 0; x <= 20; x++)
        {
                numbers[x] = 20 - x;
        	printf("Position %d is %d.\n", x, numbers[x]);
	}
	
	printf("\n");	

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

	
	qsort(numbers, length, sizeof(int), comparator);
	
	for (int i = 0; i < length; i++)
	{
		printf("numbers[%d] = %d\n", i, numbers[i]);
	}

	return 0;
}

void swap(int *a, int *b)
{	
	
	printf("The two original numbers are %d for a and %d for b.\n", *a, *b);
	int temp = *a;
	*a = *b;
		*b = temp;
	printf("The swapped values are %d for a and %d for b.\n", *a, *b);
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

int comparator(const void *x_void, const void *y_void)
{
	int x = *(int *)x_void;
	int y = *(int *)y_void;
	return x-y;	
}
