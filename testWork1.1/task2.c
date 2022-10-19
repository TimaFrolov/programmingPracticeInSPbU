#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    const int c = *a;
    *a = *b;
    *b = c;
}

void selectionSort(size_t len, int *arr)
{
    for (size_t currentIndex = 0; currentIndex < len; ++currentIndex)
    {
        int min = arr[currentIndex];
        size_t indexOfMin = currentIndex;
        for (size_t i = currentIndex + 1; i < len; ++i)
        {
            if (arr[i] < min)
            {
                min = arr[i];
                indexOfMin = i;
            }
        }
        swap(arr + currentIndex, arr + indexOfMin);
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

    int *arr = calloc(arrSize, sizeof(int));
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

    selectionSort(arrSize, arr);
    
    printf("Sorted array:");
    for (size_t i = 0; i < arrSize; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);
}