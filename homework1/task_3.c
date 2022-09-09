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
    size_t m, n;
    printf("Input m: ");
    scanf("%llu", &m);
    printf("Input n: ");
    scanf("%llu", &n);

    int *arr = malloc((m + n) * sizeof(int));
    printf("Input arrays: ");
    for (size_t i = 0; i < m + n; ++i)
    {
        scanf("%d", &arr[i]);
    }

    reverse(m + n, arr);
    reverse(m, arr);
    reverse(n, arr + m);

    printf("Swapped arrays: ");
    for (size_t i = 0; i < m + n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
}