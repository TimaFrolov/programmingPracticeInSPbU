#include "msort.h"

#include <stdlib.h>

bool msort(List *list, bool (*compareFunction)(void *, void *))
{
    // printf("Entered merge sort! list=");
    // listPrint(list);
    // printf("\n");
    size_t len = 0;
    listLen(list, &len);
    if (len <= 1)
    {
        return true;
    }

    List *list1 = NULL, *list2 = NULL;

    size_t elementSize = 0;

    listElementSize(list, &elementSize);

    int errorCode1 = createList(&list1, elementSize);
    int errorCode2 = createList(&list2, elementSize);

    if (errorCode1 || errorCode2)
    {
        free(list1);
        free(list2);
        return false;
    }

    listPartition(list, list1, list2);

    // printf("Partition made! list1=");
    // listPrint(list1);
    // printf(", list2=");
    // listPrint(list2);
    // printf("\n");

    bool result1 = msort(list1, compareFunction);
    // printf("Sorted list1! list1=");
    // listPrint(list1);
    // printf("\n");
    bool result2 = msort(list2, compareFunction);
    // printf("Sorted list2! list2=");
    // listPrint(list2);
    // printf("\n");

    if (!result1 || !result2)
    {
        free(list1);
        free(list2);
        return false;
    }

    listMerge(list1, list2, list, compareFunction);
    // printf("Merged lists! list=");
    // listPrint(list);
    // printf("\n");

    free(list1);
    free(list2);
    return true;
}