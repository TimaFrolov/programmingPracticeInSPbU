#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

#define arrElementType short

#define maxNum 1000

void swap(arrElementType *a, arrElementType *b)
{
    arrElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

void generate(size_t len, arrElementType *arr)
{
    for (size_t i = 0; i < len; ++i)
    {
        arr[i] = rand() % maxNum;
    }
}

void partition(size_t len, arrElementType *arr, arrElementType element)
{
    arrElementType *leftPtr = arr, *rightPtr = arr + len - 1;

    while (leftPtr < rightPtr)
    {
        while (leftPtr <= rightPtr && element >= *leftPtr)
        {
            ++leftPtr;
        }

        while (rightPtr > leftPtr && element < *rightPtr)
        {
            --rightPtr;
        }

        if (leftPtr < rightPtr)
        {
            swap(leftPtr, rightPtr);
        }
    }
    
    if (leftPtr > arr)
    {
        swap(arr, leftPtr - 1);
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

    uint seed = 0;
    printf("Enter seed for random (positive number): ");
    scanResult = scanf("%u", &seed);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter positive number: ");
        scanResult = scanf("%u", &seed);
    }

    srand(seed);

    arrElementType *arr = malloc(arrSize * sizeof(arrElementType));
    if (arr == NULL)
    {
        printf("Error allocating memory for array!\n");
        return -1;
    }
    generate(arrSize, arr);

    printf("Generated array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");

    partition(arrSize, arr, arr[0]);

    printf("Transformed array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}