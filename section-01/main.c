#include <stdio.h>
#include <stdlib.h>

int FizzBuzz(int n)
{
    
        if (n % 3 == 0 && n % 5 == 0) {
            printf("FizzBuzz\n");
        } 
        else if (n % 3 == 0) {
         printf("Fizz\n");
        } 
        else if (n % 5 == 0) {
            printf("Buzz\n");
        } 
        
    


    return 0;
}

int compare_descending(const void *a, const void *b)
{
    int first = *(const int *)a;
    int second = *(const int *)b;

    if (first < second)
    {
        return 1;
    }
    else if (first > second)
    {
        return -1;
    }         
    else
    {
        return 0;
    }
}

int main(void) {
    printf("Hello, World!\n");

    int number = 10;
    int *ptr = &number;
    printf("%d\n", *ptr);
    *ptr = 20;
    printf("After: %d\n", number);

    int *num = malloc(20*sizeof(int));
    if (num == NULL) {
        printf( "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 20; i++) {
        num[i] = i + 1;
        
    }
    for (int i = 0; i < 20; i++) {
        FizzBuzz(num[i]);
    }

    printf("\nFizzBuzz using a for loop (1-30:\n");
    for (int i = 1; i <= 30; i++) {
        FizzBuzz(i);
    }
    

    qsort(num, 20, sizeof(int), compare_descending);
    
    
    printf("\nArray after sorting:\n");

    for (int i = 0; i < 20; i++)
    {
        printf("%d ", num[i]);
    }

    printf("\n");
   
    free(num);
    return 0;
}


/*
Exercise 1.1

Possible improvements:
1. Pass the input matrix as const because it is not modified.
2. Consider passing the matrix by pointer to avoid copying the struct.
3. Use size_t for matrix dimensions and array indexing.
4. Check whether create_matrix() successfully allocated memory.
5. Consider checking for invalid dimensions and integer overflow.
6. Improve variable names and readability of the indexing.
*/