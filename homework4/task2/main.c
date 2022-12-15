#include <stdio.h>
#include "sort.h"

#define PATH_MAX 4096

int find(size_t len, int *arr)
{
    int ans = 0;
    size_t maxCount = 0;
    size_t currentCount = 1;
    int currentNumber = arr[0];

    for (size_t i = 1; i < len; ++i)
    {
        if (arr[i] == currentNumber)
        {
            ++currentCount;
        }
        else
        {
            if (currentCount > maxCount)
            {
                ans = currentNumber;
                maxCount = currentCount;
            }
            currentCount = 1;
            currentNumber = arr[i];
        }
    }

    if (currentCount > maxCount)
    {
        return currentNumber;
    }
    return ans;
}

int main()
{
    char filepath[PATH_MAX] = {'\0'};

    printf("Enter file path (no longer than %d symbols)\nFile on given path should have array length at first, then array itself: ", PATH_MAX);
    scanf("%s", filepath);
    if (filepath[PATH_MAX - 1] != '\0')
    {
        printf("Given file path is too long!\n");
        return -3;
    }
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Cannot open file on given path!\n");
        return -4;
    }

    size_t arrSize = 0;
    int scanResult = fscanf(file, "%lu", &arrSize);
    if (scanResult == 0 || arrSize == 0)
    {
        printf("Given file contains incorrect data!\n");
        fclose(file);
        return -2;
    }

    int *arr = calloc(arrSize, sizeof(int));
    if (arr == NULL)
    {
        printf("Error allocating memory for array!\n");
        fclose(file);
        return -1;
    }
    for (size_t i = 0; i < arrSize; ++i)
    {
        scanResult = scanf("%d", &arr[i]);
        while (scanResult == 0)
        {
            printf("Given file contains incorrect data!\n");
            fclose(file);
            free(arr);
            return -2;
        }
    }
    fclose(file);

    sort(arrSize, arr);

    printf("Most common value in array: %d\n", find(arrSize, arr));
    free(arr);
    return 0;
}