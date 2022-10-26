#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define arrElementType int

// #define DEBUG 1

void swap(arrElementType *a, arrElementType *b)
{
    arrElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(size_t len, arrElementType *arr)
{
    for (size_t i = 0; i < len - 1; ++i)
    {
        for (size_t j = i + 1; j < len; ++j)
        {
            if (arr[i] > arr[j])
            {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

int countingSort(size_t len, arrElementType *arr)
{
    arrElementType min = arr[0], max = arr[0];
    for (size_t i = 1; i < len; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    size_t *nums = malloc(sizeof(size_t) * (max - min + 1));
    if (nums == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < len; ++i)
    {
        nums[arr[i] - min]++;
    }

    for (size_t i = 0, j = 0; i < len; ++i)
    {
        while (nums[j] == 0)
            ++j;
        arr[i] = j + min;
        --nums[j];
    }
    free(nums);

    return 0;
}

#ifdef DEBUG
int test1()
{
    int testResult = 0;

    arrElementType arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    bubbleSort(10, arr);
    bool isTestFailed = false;

    for (int i = 0; i < 10; ++i)
    {
        if (arr[i] != i + 1)
        {
            isTestFailed = true;
            break;
        }
    }

    if (isTestFailed)
    {
        printf("Test failed! Initial array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}. Array after bubble sort: {");
        for (int i = 0; i < 9; ++i)
        {
            printf("%d, ", arr[i]);
        }
        printf("%d}\n", arr[9]);
        testResult = -1;
    }
    return testResult;
}
int test2()
{
    int testResult = 0;

    arrElementType arr[10] = {10, 9, 8, 7, 6, 5, 10, 3, 2, 1};
    for (int i = 0; i < 10; ++i)
    {
        arr[i] = 10 - i;
    }
    arr[6] = 10;

    countingSort(10, arr);
    bool isTestFailed = false;

    for (int i = 0; i < 10; ++i)
    {
        if ((i < 3 && arr[i] != i + 1) || (i == 3 && arr[i] != 5) || (i > 3 && i < 8 && arr[i] != i + 2) || (i >= 8 && arr[i] != 10))
        {
            isTestFailed = true;
            break;
        }
    }

    if (isTestFailed)
    {
        printf("Test failed! Initial array = {10, 9, 8, 7, 6, 5, 10, 3, 2, 1}. Array after count sort: {");
        for (int i = 0; i < 9; ++i)
        {
            printf("%d, ", arr[i]);
        }
        printf("%d}\n", arr[9]);
        testResult = -1;
    }

    return testResult;
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test result: %d\n", test1());
    printf("Test result: %d\n", test2());
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

    arrElementType *arr = malloc(arrSize * sizeof(arrElementType));
    arrElementType *arr2 = malloc(arrSize * sizeof(arrElementType));
    if (arr == NULL || arr2 == NULL)
    {
        printf("Error allocating memory for array!\n");
        free(arr);
        free(arr2);
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

    for (size_t i = 0; i < arrSize; ++i)
    {
        arr2[i] = arr[i];
    }

    const clock_t clockAtStartBubble = clock();
    bubbleSort(arrSize, arr);
    const clock_t clockAtEndBubble = clock();

    printf("Bubble sort took %.6f seconds! Sorted array:", (float)(clockAtEndBubble - clockAtStartBubble) / CLOCKS_PER_SEC);
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);

    const clock_t clockAtStartCount = clock();
    int errorCode = countingSort(arrSize, arr2);
    if (errorCode == -1)
    {
        printf("Error allocating memory for array!\n");
        return errorCode;
    }
    const clock_t clockAtEndCount = clock();

    printf("Count sort took %.6f seconds! Sorted array:", (float)(clockAtEndCount - clockAtStartCount) / CLOCKS_PER_SEC);
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr2[i]);
    }
    printf("\n");
    free(arr2);
}