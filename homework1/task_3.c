#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    const int tmp = *b;
    *b = *a;
    *a = tmp;
}

void reverse(size_t len, int *arr)
{
    for (size_t i = 0; i < len / 2; ++i)
    {
        swap(&arr[i], &arr[len - i - 1]);
    }
}

int main()
{
    size_t firstSubarraySize, secondSubarraySize;
    printf("Input first subarray size: ");
    scanf("%lu", &firstSubarraySize);
    printf("Input second subarray size: ");
    scanf("%lu", &secondSubarraySize);

    int *arr = malloc((secondSubarraySize + firstSubarraySize) * sizeof(int));
    printf("Input arrays: ");
    for (size_t i = 0; i < secondSubarraySize + firstSubarraySize; ++i)
    {
        scanf("%d", &arr[i]);
    }

    reverse(secondSubarraySize + firstSubarraySize, arr);
    reverse(secondSubarraySize, arr);
    reverse(firstSubarraySize, arr + secondSubarraySize);

    printf("Swapped arrays: ");
    for (size_t i = 0; i < secondSubarraySize + firstSubarraySize; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
}