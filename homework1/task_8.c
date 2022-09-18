#include <stdio.h>

int main()
{
    size_t arrayLength = 0;
    printf("Enter length of an array: ");
    scanf("%llu", &arrayLength);
    
    printf("Enter array: ");
    size_t numberOfZeroes = 0;
    for (size_t i = 0; i < arrayLength; ++i)
    {
        int element;
        scanf("%d", &element);
        if (element == 0)
        {
            numberOfZeroes++;
        }
    }
    printf("Number of elements zeroes in given array: %llu\n", numberOfZeroes);
}