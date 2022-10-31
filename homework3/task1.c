#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define arrElementType int

// #define DEBUG 1

void swap(arrElementType *a, arrElementType *b)
{
    const arrElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertionSort(size_t len, arrElementType *arr)
{
    for (size_t i = 1; i < len; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr + j, arr + j - 1);
            }
            else {
                break;
            }
        }
    }
}

size_t partition(size_t len, arrElementType *arr)
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

    const arrElementType pivot = arr[center];
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

void sort(size_t len, arrElementType *arr)
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
bool test1()
{
    bool testResult = true;

    int arr[] = {6, 9, 16, 8, 3, 19, 11, 18, 10, 20, 15, 17, 7, 12, 4, 2, 14, 13, 1, 5};
    sort(20, arr);
    for (int i = 0; i < 20; ++i)
    {
        if (arr[i] != i + 1)
        {
            testResult = false;
            break;
        }
    }

    if (!testResult)
    {
        printf("Test failed! Initial array = {6, 9, 16, 8, 3, 19, 11, 18, 10, 20, 15, 17, 7, 12, 4, 2, 14, 13, 1, 5}. Array after sort: {");
        for (int i = 0; i < 19; ++i)
        {
            printf("%d, ", arr[i]);
        }
        printf("%d}\n", arr[19]);
    }

    return testResult;
}

bool test2()
{
    bool testResult = true;

    int arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    sort(12, arr2);
    for (int i = 0; i < 12; ++i)
    {
        if (arr2[i] != 1)
        {
            testResult = false;
            break;
        }
    }
    if (!testResult)
    {
        printf("Test failed! Initial array = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}. Array after sort: {");
        for (int i = 0; i < 11; ++i)
        {
            printf("%d, ", arr2[i]);
        }
        printf("%d}\n", arr2[12]);
    }

    return testResult;
}
#endif

int main()
{
#ifdef DEBUG
    printf("First test result: %d\n", test1());
    printf("Second test result: %d\n", test2());
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

    arrElementType *arr = calloc(arrSize, sizeof(arrElementType));
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