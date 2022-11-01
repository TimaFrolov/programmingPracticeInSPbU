#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define byte signed char

int main()
{
    SortedList *list = NULL;
    int errorCode = createList(&list);
    if (errorCode == -1)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    byte command = 0;
    do
    {
        printf("Input command (0 - exit, 1 - add value to list, 2 - remove value from list, 3 - print list): ");
        int scanResult = scanf("%hhi", &command);
        while (scanResult == 0 || command > 3 || command < 0)
        {
            scanf("%*[^\n]");
            printf("Wrong input! Please try again: ");
            scanResult = scanf("%hhi", &command);
        }
        switch (command)
        {
        case 1:
        {
            printf("Enter integer number to add it to list: ");
            int value = 0;
            int scanResult = scanf("%d", &value);
            while (scanResult == 0)
            {
                scanf("%*[^\n]");
                printf("Wrong input! Please try again: ");
                scanResult = scanf("%d", &value);
            }
            int appendResult = listAppend(list, value);
            printf(appendResult == 0 ? "Succesfully added value to list\n" : "Error allocating memory, try again\n");
            break;
        }
        case 2:
        {
            printf("Enter integer number to remove it from list: ");
            int value = 0;
            int scanResult = scanf("%d", &value);
            while (scanResult == 0)
            {
                scanf("%*[^\n]");
                printf("Wrong input! Please try again: ");
                scanResult = scanf("%d", &value);
            }
            int removeResult = listRemove(list, value);
            printf(removeResult == 1 ? "Succesfully removed value from list\n" : "No such value in list\n");
            break;
        }
        case 3:
        {
            printf("Current state of list: ");
            listPrint(list);
            printf("\n");
            break;
        }
        }
    } while (command != 0);

    listFree(list);
    free(list);
    return 0;
}