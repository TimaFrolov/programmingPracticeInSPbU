#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    const int c = *a;
    *a = *b;
    *b = c;
}

bool isSorted(int *arr, size_t len)
{
    for (size_t i = 1; i < len; ++i)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }
    return true;
}

void shuffle(int *arr, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        swap(&arr[i], &arr[rand() % len]);
    }
}

void bogoSort(int *arr, size_t len)
{
    while (!isSorted(arr, len))
    {
        shuffle(arr, len);
    }
}

int main()
{
    printf("Enter length of array (natural number): ");
    size_t len = 0;
    int scanResult = scanf("%lu", &len);
    while (scanResult == 0 || len == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please enter natural number: ");
        scanResult = scanf("%lu", &len);
    }

    int *arr = calloc(len, sizeof(int));
    if (arr == NULL)
    {
        printf("Error allocating memory for array!\n");
        return -1;
    }

    printf("Input array of numbers: ");
    for (size_t i = 0; i < len; ++i)
    {
        int scanResult = scanf("%d", &arr[i]);
        if (scanResult == 0)
        {
            scanf("%*[^\n]");
            i = 0;
            printf("Incorrect input! Please enter numbers only: ");
        }
    }

    printf("Enter seed for rand() function (natural number): ");
    unsigned int seed = 0;
    scanResult = scanf("%u", &seed);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please enter natural number: ");
        scanResult = scanf("%u", &seed);
    }
    srand(seed);

    const clock_t timeAtStart = clock();
    bogoSort(arr, len);
    const clock_t timeAtEnd = clock();
    printf("Bogosort took %.6f seconds!\n", (float)(timeAtEnd - timeAtStart) / CLOCKS_PER_SEC);

    printf("Sorted array:");
    for (size_t i = 0; i < len; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    free(arr);

    return 0;
}