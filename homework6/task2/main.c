#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int getLastSurvivedWarrior(int amountOfWarriors, int stepOfKilling, int *lastSurvivedWarriorPtr)
{
    if (lastSurvivedWarriorPtr == NULL) {
        return GivenPointerIsNULL;
    }

    CyclicList *list = NULL;
    Error errorCode = createList(&list);
    if (errorCode == MemoryAllocationError)
    {
        return MemoryAllocationError;
    }

    for (int i = 0; i < amountOfWarriors; ++i)
    {
        Error errorCode = listInsert(list, i, -1);
        if (errorCode == MemoryAllocationError)
        {
            listFree(list);
            free(list);
            return -1;
        }
    }

    listRemoveEach(list, stepOfKilling, stepOfKilling, amountOfWarriors - 1);

    int last = -1;
    listGet(list, &last, 0);

    *lastSurvivedWarriorPtr = last;
    listFree(list);
    free(list);
    return OK;
}

int main()
{

    int amountOfWarriors = 0, stepOfKilling = 0;
    printf("Enter amount of warriors: ");
    int scanResult = scanf("%d", &amountOfWarriors);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please try again: ");
        scanResult = scanf("%d", &amountOfWarriors);
    }
    printf("Enter step with which warriors are getting killed: ");
    scanResult = scanf("%d", &stepOfKilling);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please try again: ");
        scanResult = scanf("%d", &stepOfKilling);
    }

    int last = -1;
    int errorCode = getLastSurvivedWarrior(amountOfWarriors, stepOfKilling, &last);
    if (errorCode == MemoryAllocationError)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    printf("Last warrior was initially staying on position %d\n", last);

    return 0;
}