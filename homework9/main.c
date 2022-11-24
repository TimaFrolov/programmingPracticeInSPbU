#include <stdio.h>

#include "hashMap.h"

int main()
{
    char filename[101] = {0};
    printf("Enter file path (no longer than 100 symbols): ");
    scanf("%100s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("That file doesn't exist!\n");
        return -2;
    }

    HashMap *hashMap = NULL;
    Error creationError = createHashMap(&hashMap);
    if (creationError == MemoryAllocationError)
    {
        fclose(file);
        printf("Memory allocation error!\n");
        return -1;
    }

    char buffer[1000] = {0};
    while (!feof(file))
    {
        fscanf(file, "%1000s", buffer);
        size_t curAmount = 0;
        hashMapGet(hashMap, buffer, 0, &curAmount);
        Error insertionError = hashMapInsert(hashMap, buffer, curAmount + 1);
        if (insertionError == MemoryAllocationError)
        {
            fclose(file);
            hashMapFree(hashMap);
            printf("Memory allocation error!\n");
            return -1;
        }
    }
    fclose(file);

    printf("Amount of words in text:\n");
    hashMapPrint(hashMap);
    printf("\n");
    hashMapPrintDebugInfo(hashMap);

    hashMapFree(hashMap);
    return 0;
}