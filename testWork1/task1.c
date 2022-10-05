#include <stdio.h>
#include <stdlib.h>

// #define DEBUG 1

#define arrType int

void swap(arrType *a, arrType *b)
{
    const arrType c = *a;
    *a = *b;
    *b = c;
}

void insertionSort(size_t len, arrType *arr)
{
    for (size_t i = 0; i < len; ++i)
    {
        if (arr[i] % 2 == 0)
        {
            for (size_t currentIndex = i,
                        previousIndex = i - 1;
                 currentIndex > 0; --previousIndex)
            {
                while (previousIndex > 0 && arr[previousIndex] % 2)
                {
                    --previousIndex;
                }
                if (previousIndex == 0 && arr[previousIndex] % 2)
                {
                    break;
                }

                if (arr[currentIndex] < arr[previousIndex])
                {
                    swap(arr + currentIndex, arr + previousIndex);
                    currentIndex = previousIndex;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

#ifdef DEBUG
int test()
{
    int testResult = 0;

    int arr[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    insertionSort(10, arr);
    int isTestFailed = 0;
    for (size_t i = 0; i < 10; ++i)
    {
        if (i % 2 == 0 && arr[i] != (int)(9 - i))
        {
            isTestFailed = 1;
            break;
        }

        else if (i % 2 && arr[i] != (int)(i - 1))
        {
            isTestFailed = 1;
            break;
        }
    }
    if (isTestFailed)
    {
        printf("Test failed! Initial array = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}. Array after sort: {");
        for (int i = 0; i < 9; ++i)
        {
            printf("%d, ", arr[i]);
        }
        printf("%d}\n", arr[9]);
        testResult = -2;
    }

    int arr2[5] = {6, 4, 3, 2, 1};
    insertionSort(5, arr2);
    if (arr2[0] != 2 || arr2[1] != 4 || arr2[2] != 3 || arr2[3] != 6 || arr2[4] != 1)
    {
        printf("Test failed! Initial array = {6, 4, 3, 2, 1}. Array after sort: {");
        for (int i = 0; i < 4; ++i)
        {
            printf("%d, ", arr2[i]);
        }
        printf("%d}\n", arr2[4]);
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

    insertionSort(arrSize, arr);

    printf("Sorted array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);
}