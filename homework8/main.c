#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define byte signed char

int main()
{
    Map *map = createMap();

    byte command = 0;
    do
    {
        printf("Input command (0 - exit, 1 - add value to map, 2 - get value by key from list, 3 - check if key in map, 4 - remove key from map): ");
        int scanResult = scanf("%hhi", &command);
        while (scanResult == 0 || command > 4 || command < 0)
        {
            scanf("%*[^\n]");
            printf("Incorrect input! Please try again: ");
            scanResult = scanf("%hhi", &command);
        }
        switch (command)
        {
        case 1:
        {
            char *key = calloc(101, sizeof(char));
            char *value = calloc(101, sizeof(char));
            if (value == NULL || key == NULL)
            {
                printf("Error allocating memory!\n");
                free(key);
                free(value);
                free(map);
                return -1;
            }
            printf("Enter key (string no longer than 100 symbols) to add to map: ");
            scanf("%s", key);
            while (key[100] != '\0')
            {
                scanf("%*[^\n]");
                printf("Given string is too long! Please try again: ");
                for (size_t i = 0; i < 101; ++i)
                {
                    key[i] = '\0';
                }
                scanf("%s", key);
            }
            printf("Enter value (string no longer than 100 symbols) to add to map: ");
            scanf("%s", value);
            while (value[100] != '\0')
            {
                scanf("%*[^\n]");
                printf("Given string is too long! Please try again: ");
                for (size_t i = 0; i < 101; ++i)
                {
                    value[i] = '\0';
                }
                scanf("%s", value);
            }
            Error insertResult = mapInsert(&map, key, value);
            if (insertResult == MemoryAllocationError)
            {
                printf("Error allocating memory!\n");
                return -1;
            }
            printf("Value was succesfully added to map!\n");
            free(value);
            break;
        }
        case 2:
        {
            char *key = calloc(101, sizeof(char));
            if (key == NULL)
            {
                printf("Error allocating memory!\n");
                free(map);
                return -1;
            }
            printf("Enter key (string no longer than 100 symbols) to get value from map: ");
            scanf("%s", key);
            while (key[100] != '\0')
            {
                scanf("%*[^\n]");
                printf("Given string is too long! Please try again: ");
                for (size_t i = 0; i < 101; ++i)
                {
                    key[i] = '\0';
                }
                scanf("%s", key);
            }
            char *value = NULL;
            Error getResult = mapGet(map, key, &value);
            if (getResult == MemoryAllocationError)
            {
                printf("Error allocating memory!\n");
                return -1;
            }
            if (value == NULL)
            {
                printf("No such key in map\n");
                break;
            }
            printf("Value by given key is: %s\n", value);
            free(value);
            break;
        }
        case 3:
        {
            char *key = calloc(101, sizeof(char));
            if (key == NULL)
            {
                printf("Error allocating memory!\n");
                free(map);
                return -1;
            }
            printf("Enter key (string no longer than 100 symbols) to check if it is in map: ");
            scanf("%s", key);
            while (key[100] != '\0')
            {
                scanf("%*[^\n]");
                printf("Given string is too long! Please try again: ");
                for (size_t i = 0; i < 101; ++i)
                {
                    key[i] = '\0';
                }
                scanf("%s", key);
            }


            if (mapContains(map, key))
            {
                printf("Map contains this key!\n");
                break;
            }
            printf("No such key in map\n");
            break;
        }
        case 4:
        {
            char *key = calloc(101, sizeof(char));
            if (key == NULL)
            {
                printf("Error allocating memory!\n");
                free(map);
                return -1;
            }
            printf("Enter key (string no longer than 100 symbols) to remove from map: ");
            scanf("%s", key);
            while (key[100] != '\0')
            {
                scanf("%*[^\n]");
                printf("Given string is too long! Please try again: ");
                for (size_t i = 0; i < 101; ++i)
                {
                    key[i] = '\0';
                }
                scanf("%s", key);
            }

            map = mapPop(map, key);
            printf("Removed given key from map!\n");
            break;
        }
        }
    } while (command != 0);

    mapFree(map);
    return 0;
}