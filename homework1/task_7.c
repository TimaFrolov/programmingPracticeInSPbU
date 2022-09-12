#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

const int SQRT_OF_MAX_INT = 46340;

int main()
{
    int maxNumber;
    printf("Enter number: ");
    scanf("%d", &maxNumber);
    printf("Prime numbers lower than %d", maxNumber);
    maxNumber++;

    bool *isPrime = malloc(maxNumber * sizeof(bool));
    for (int i = 2; i < maxNumber; ++i)
    {
        isPrime[i] = 1;
    }
    isPrime[0] = isPrime[1] = 0;

    for (int number = 2; number < maxNumber; ++number)
    {
        if (isPrime[number])
        {
            printf("%d ", number);
            if (number < SQRT_OF_MAX_INT) // checking that number^2 will be positive
            {
                for (int numberMultiple = number * number; numberMultiple < maxNumber; numberMultiple += number)
                {
                    isPrime[numberMultiple] = 0;
                }
            }
        }
    }
    free(isPrime);
    printf("\n");
}