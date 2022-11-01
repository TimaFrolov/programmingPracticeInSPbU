#include <stdio.h>

#include "list.h"

int main()
{
    CyclicList *list = NULL;
    Error errorCode = createList(&list);
    if (errorCode == MemoryAllocationError)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    int amountOfWarriors, stepOfKilling;
    printf("Enter amount of warriors: ");
    scanf("%d", &amountOfWarriors);
    printf("Enter step with which warriors are getting killed: ");
    scanf("%d", &stepOfKilling);

    for (int i = 0; i < amountOfWarriors; ++i)
    {
        Error errorCode = listInsert(list, i, -1);
        if (errorCode == MemoryAllocationError)
        {
            printf("Error allocating memory!\n");
            return -1;
        }
    }

    listRemoveEach(list, stepOfKilling, stepOfKilling, amountOfWarriors - 1);

    int last = -1;
    listGet(list, &last, 0);

    printf("Last warrior was initially staying on position %d\n", last);

    listFree(list);
    free(list);
    return 0;
}