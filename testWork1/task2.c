#include <stdio.h>
#include <stdlib.h>

#define arrType int

void swap(arrType *a, arrType *b)
{
    const arrType c = *a;
    *a = *b;
    *b = c;
}

size_t getMaxStep(size_t len)
{
    size_t ans = 1;
    while (ans < len)
    {
        ans <<= 1;
        ans++;
    }
    return ans >> 1;
}

void shellSort(size_t len, arrType *arr)
{
    for (size_t step = getMaxStep(len); step > 0; step >>= 1)
    {
        for (size_t i = 0; i < len - step; ++i)
        {
            for (size_t j = i + step; j < len; j += step)
            {
                if (arr[i] > arr[j])
                {
                    swap(arr + i, arr + j);
                }
            }
        }
    }
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

    shellSort(arrSize, arr);
    
    printf("Sorted array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);
}