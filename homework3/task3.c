#include <stdio.h>
#include <stdlib.h>

#define arrType int

// #define DEBUG 1

int comparatorFunc(const void *a, const void *b)
{
    return (*(arrType *)a > *(arrType *)b) - (*(arrType *)a < *(arrType *)b);
}

arrType find(size_t len, arrType *arr)
{
    arrType ans = 0;
    size_t maxCount = 0;
    size_t currentCount = 1;
    arrType currentNumber = arr[0];

    for (size_t i = 1; i < len; ++i)
    {
        if (arr[i] == currentNumber)
        {
            ++currentCount;
        }
        else
        {
            if (currentCount > maxCount)
            {
                ans = currentNumber;
                maxCount = currentCount;
            }
            currentCount = 1;
            currentNumber = arr[i];
        }
    }

    if (currentCount > maxCount)
    {
        return currentNumber;
    }
    return ans;
}

int main()
{
    size_t arrSize = 0;
    printf("Enter array size: ");
    int scanResult = scanf("%lu", &arrSize);
    while (scanResult == 0 || arrSize == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%lu", &arrSize);
    }

    arrType *arr = calloc(arrSize, sizeof(arrType));
    if (arr == NULL)
    {
        printf("Error allocating memory for array!\n");
        return -1;
    }
    printf("Input array of numbers: ");
    for (size_t i = 0; i < arrSize; ++i)
    {
        scanResult = scanf("%d", &arr[i]);
        while (scanResult == 0)
        {
            scanf("%*[^\n]");
            printf("Wrong input! Please enter numbers only: ");
            scanResult = scanf("%d", &arr[i]);
        }
    }

    qsort(arr, arrSize, sizeof(arrType), comparatorFunc);

#ifdef DEBUG
    printf("Sorted array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
#endif

    printf("Most common value in array: %d\n", find(arrSize, arr));

    free(arr);
}