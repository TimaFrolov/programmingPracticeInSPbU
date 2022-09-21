#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

#define arrType short

#define maxNum 1000

void swap(arrType *a, arrType *b)
{
    arrType tmp = *a;
    *a = *b;
    *b = tmp;
}

void generate(size_t len, arrType *arr)
{
    for (size_t i = 0; i < len; ++i)
    {
        arr[i] = rand() % maxNum;
    }
}

void transform(size_t len, arrType *arr)
{
    arrType element = arr[0];
    arrType *leftPtr = arr, *rightPtr = arr + len - 1;

    while (leftPtr < rightPtr)
    {
        while (element > *leftPtr)
        {
            ++leftPtr;
        }

        while (element < *rightPtr)
        {
            --rightPtr;
        }

        if (leftPtr < rightPtr)
        {
            swap(leftPtr, rightPtr);
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

    arrType *arr = malloc(arrSize * sizeof(arrType));
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

    transform(arrSize, arr);

    printf("Transformed array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}