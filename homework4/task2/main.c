#include <stdio.h>
#include "sort.h"

#define PATH_MAX 4096

int findMostCommonNumber(size_t len, int *array)
{
    int mostCommonNumber = 0;
    size_t maxCount = 0;
    size_t currentNumberCount = 1;
    int currentNumber = array[0];

    for (size_t i = 1; i < len; ++i)
    {
        if (array[i] == currentNumber)
        {
            ++currentNumberCount;
        }
        else
        {
            if (currentNumberCount > maxCount)
            {
                mostCommonNumber = currentNumber;
                maxCount = currentNumberCount;
            }
            currentNumberCount = 1;
            currentNumber = array[i];
        }
    }

    if (currentNumberCount > maxCount)
    {
        return currentNumber;
    }
    return mostCommonNumber;
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

    int *array = calloc(arrSize, sizeof(int));
    if (array == NULL)
    {
        printf("Error allocating memory for array!\n");
        fclose(file);
        return -1;
    }
    for (size_t i = 0; i < arrSize; ++i)
    {
        scanResult = scanf("%d", &array[i]);
        while (scanResult == 0)
        {
            printf("Given file contains incorrect data!\n");
            fclose(file);
            free(array);
            return -2;
        }
    }
    fclose(file);

    sort(arrSize, array);

    printf("Most common value in array: %d\n", findMostCommonNumber(arrSize, array));
    free(array);
    return 0;
}