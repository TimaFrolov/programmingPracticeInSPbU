#include <stdio.h>
#include <stdlib.h>

#define arrType int

// #define DEBUG 1

void swap(arrType *a, arrType *b)
{
    const arrType tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertionSort(size_t len, arrType *arr)
{
    for (size_t i = 0; i < len; ++i)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < len; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            swap(&arr[minIndex], &arr[i]);
        }
    }
}

size_t partition(size_t len, arrType *arr)
{
    const size_t center = len / 2;

    if (arr[0] > arr[center])
    {
        swap(arr + 0, arr + center);
    }
    if (arr[center] > arr[len - 1])
    {
        swap(arr + center, arr + len - 1);
    }

    const arrType pivot = arr[center];
    size_t leftIndex = 0, rightIndex = len - 1;

    while (leftIndex < rightIndex)
    {
        while (leftIndex < len && pivot >= arr[leftIndex])
        {
            ++leftIndex;
        }

        while (pivot < arr[rightIndex])
        {
            --rightIndex;
        }

        if (leftIndex < rightIndex)
        {
            swap(arr + leftIndex, arr + rightIndex);
        }
    }

    return leftIndex;
}

void sort(size_t len, arrType *arr)
{
    if (len <= 10)
    {
        insertionSort(len, arr);
        return;
    }

    const size_t part = partition(len, arr);

    if (part >= len)
    {
        return;
    }

    sort(part, arr);
    sort(len - part, arr + part);
}

#ifdef DEBUG
int test()
{
    int testResult = 0;

    int arr[] = {6, 9, 16, 8, 3, 19, 11, 18, 10, 20, 15, 17, 7, 12, 4, 2, 14, 13, 1, 5};
    sort(20, arr);
    int isTestFailed = 0;
    for (int i = 0; i < 20; ++i)
    {
        if (arr[i] != i + 1)
        {
            isTestFailed = 1;
            break;
        }
    }

    if (isTestFailed)
    {
        printf("Test failed! Initial array = {6, 9, 16, 8, 3, 19, 11, 18, 10, 20, 15, 17, 7, 12, 4, 2, 14, 13, 1, 5}. Array after sort: {");
        for (int i = 0; i < 19; ++i)
        {
            printf("%d, ", arr[i]);
        }
        printf("%d}\n", arr[19]);
        testResult = -2;
    }

    int arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    sort(12, arr2);
    isTestFailed = 0;
    for (int i = 0; i < 12; ++i)
    {
        if (arr2[i] != 1)
        {
            isTestFailed = 1;
            break;
        }
    }
    if (isTestFailed)
    {
        printf("Test failed! Initial array = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}. Array after sort: {");
        for (int i = 0; i < 11; ++i)
        {
            printf("%d, ", arr2[i]);
        }
        printf("%d}\n", arr2[12]);
        testResult = -2;
    }

    return testResult;
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test result: %d\n", test());
#endif
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

    sort(arrSize, arr);

    printf("Sorted array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}