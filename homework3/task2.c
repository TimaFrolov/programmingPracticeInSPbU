#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define uint unsigned int

#define maxNum 20

void generate(size_t len, int *arr)
{
    for (size_t i = 0; i < len; ++i)
    {
        arr[i] = rand() % maxNum;
    }
}

int comparatorFunc(const void *a, const void *b)
{
    return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

bool binarySearch(size_t len, int *arr, int value)
{
    size_t leftIndex = 0, rightIndex = len - 1;

    while (leftIndex < rightIndex)
    {
        const size_t centerIndex = (leftIndex + rightIndex) / 2;

        if (arr[centerIndex] == value)
        {
            return 1;
        }
        if (arr[centerIndex] < value)
        {
            leftIndex = centerIndex + 1;
        }
        else
        {
            rightIndex = centerIndex - 1;
        }
    }
    return arr[leftIndex] == value;
}

int main()
{
    size_t arrSize = 0, randomNumberAmount = 0;
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

    int *arr = calloc(arrSize, sizeof(int));
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

    qsort(arr, arrSize, sizeof(int), comparatorFunc);

    printf("Enter amount of random numbers to generate: ");
    scanResult = scanf("%lu", &randomNumberAmount);
    while (scanResult == 0 || randomNumberAmount == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%lu", &randomNumberAmount);
    }

    for (size_t i = 0; i < randomNumberAmount; ++i)
    {
        int randomNumber = 0;
        generate(1, &randomNumber);

        if (binarySearch(arrSize, arr, randomNumber))
        {
            printf("%d in generated array!\n", randomNumber);
        }
        else
        {
            printf("%d not in generated array :(\n", randomNumber);
        }
    }

    free(arr);
    return 0;
}