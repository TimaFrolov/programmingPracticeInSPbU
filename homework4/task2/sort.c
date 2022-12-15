#include "sort.h"

#include <stdlib.h>

void swap(int *a, int *b)
{
    const int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertionSort(size_t len, int *arr)
{
    for (size_t i = 1; i < len; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr + j, arr + j - 1);
            }
            else
            {
                break;
            }
        }
    }
}

size_t partition(size_t len, int *arr)
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

    const int pivot = arr[center];
    size_t leftIndex = 0, rightIndex = len - 1;

    while (leftIndex < rightIndex)
    {
        while (leftIndex < len - 1 && pivot >= arr[leftIndex])
        {
            ++leftIndex;
        }

        while (rightIndex > leftIndex && pivot < arr[rightIndex])
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

void sort(size_t len, int *arr)
{
    if (len < 10)
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