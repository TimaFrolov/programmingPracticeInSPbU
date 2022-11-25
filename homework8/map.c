#include "map.h"

#include <stdlib.h>
#include <string.h>

typedef enum
{
    EQUAL = 0,
    LEFT1 = -1,
    LEFT2 = -2,
    RIGHT1 = 1,
    RIGHT2 = 2
} Balance;

typedef struct Map
{
    char *key;
    char *value;
    Balance balance;
    struct Map *leftChild, *rightChild;
} Map;

Map *createMap()
{
    return NULL;
}

Map *rotateLeft(Map *map)
{
    Map *rightChild = map->rightChild;
    Map *leftChild = rightChild->leftChild;
    rightChild->leftChild = map;
    map->rightChild = leftChild;

    map->balance -= rightChild->balance;
    map->balance--;
    rightChild->balance--;

    return rightChild;
}

Map *bigRotateLeft(Map *map)
{
    Map *rightChild = map->rightChild;
    Map *leftChild = rightChild->leftChild;
    map->rightChild = leftChild->leftChild;
    rightChild->leftChild = leftChild->rightChild;
    leftChild->leftChild = map;
    leftChild->rightChild = rightChild;

    map->balance = leftChild->balance == RIGHT1 ? LEFT1 : EQUAL;
    rightChild->balance = leftChild->balance == LEFT1 ? RIGHT1 : EQUAL;
    leftChild->balance = EQUAL;

    return leftChild;
}

Map *rotateRight(Map *map)
{
    Map *leftChild = map->leftChild;
    Map *rightChild = leftChild->rightChild;
    leftChild->rightChild = map;
    map->leftChild = rightChild;

    map->balance += leftChild->balance;
    map->balance++;
    leftChild->balance++;

    return leftChild;
}

Map *bigRotateRight(Map *map)
{
    Map *leftChild = map->leftChild;
    Map *rightChild = leftChild->rightChild;
    map->leftChild = rightChild->rightChild;
    leftChild->rightChild = rightChild->leftChild;
    rightChild->rightChild = map;
    rightChild->leftChild = leftChild;

    map->balance = rightChild->balance == LEFT1 ? RIGHT1 : EQUAL;
    leftChild->balance = rightChild->balance == RIGHT1 ? LEFT1 : EQUAL;
    rightChild->balance = EQUAL;

    return rightChild;
}

Map *balance(Map *map)
{
    if (map == NULL)
    {
        return NULL;
    }

    if (map->balance == RIGHT2)
    {
        if (map->rightChild->balance >= 0)
        {
            return rotateLeft(map);
        }
        return bigRotateLeft(map);
    }
    if (map->balance == LEFT2)
    {
        if (map->leftChild->balance <= 0)
        {
            return rotateRight(map);
        }
        return bigRotateRight(map);
    }

    return map;
}

Error mapInsert(Map **mapPtr, char *key, char *value)
{
    if (key == NULL || value == NULL)
    {
        return GivenCharPointerIsNULL;
    }

    if (*mapPtr == NULL)
    {
        *mapPtr = calloc(1, sizeof(Map));
        if (*mapPtr == NULL)
        {
            return MemoryAllocationError;
        }
        (*mapPtr)->key = calloc(strlen(key), sizeof(char));
        (*mapPtr)->value = calloc(strlen(value), sizeof(char));
        if ((*mapPtr)->key == NULL || (*mapPtr)->value == NULL)
        {
            free((*mapPtr)->key);
            free((*mapPtr)->value);
            free(*mapPtr);
            *mapPtr = NULL;
            return MemoryAllocationError;
        }
        strcpy((*mapPtr)->key, key);
        strcpy((*mapPtr)->value, value);
        return OK;
    }

    int t = strcmp(key, (*mapPtr)->key);

    if (t == 0)
    {
        char *oldValue = (*mapPtr)->value;
        (*mapPtr)->value = calloc(strlen(value), sizeof(char));
        if ((*mapPtr)->value == NULL)
        {
            return MemoryAllocationError;
        }
        strcpy((*mapPtr)->value, value);
        free(oldValue);
        return OK;
    }
    if (t < 0)
    {
        if ((*mapPtr)->leftChild == NULL)
        {
            Error error = mapInsert(&((*mapPtr)->leftChild), key, value);
            if (error)
            {
                return error;
            }
            (*mapPtr)->balance--;
            *mapPtr = balance(*mapPtr);
            return OK;
        }
        Balance prevChildBalance = (*mapPtr)->leftChild->balance;
        Error error = mapInsert(&((*mapPtr)->leftChild), key, value);
        if (error)
        {
            return error;
        }
        Balance newChildBalance = (*mapPtr)->leftChild->balance;
        if (newChildBalance && !prevChildBalance)
        {
            (*mapPtr)->balance--;
        }

        *mapPtr = balance(*mapPtr);
        return OK;
    }
    if ((*mapPtr)->rightChild == NULL)
    {
        mapInsert(&((*mapPtr)->rightChild), key, value);
        (*mapPtr)->balance++;
        *mapPtr = balance(*mapPtr);
        return OK;
    }
    Balance prevChildBalance = (*mapPtr)->rightChild->balance;
    Error error = mapInsert(&((*mapPtr)->rightChild), key, value);
    if (error)
    {
        return error;
    }
    Balance newChildBalance = (*mapPtr)->rightChild->balance;
    if (newChildBalance && !prevChildBalance)
    {
        (*mapPtr)->balance++;
    }

    *mapPtr = balance(*mapPtr);
    return OK;
}

Error mapGet(Map *map, char *key, char **value)
{
    if (key == NULL || value == NULL)
    {
        return GivenCharPointerIsNULL;
    }

    while (map != NULL)
    {
        int t = strcmp(key, map->key);
        if (t == 0)
        {
            *value = calloc(strlen(map->value) + 1, sizeof(char));
            if (value == NULL)
            {
                return MemoryAllocationError;
            }
            strcpy(*value, map->value);
            return OK;
        }
        if (t < 0)
        {
            map = map->leftChild;
            continue;
        }
        map = map->rightChild;
    }
    return OK;
}

bool mapContains(Map *map, char *key)
{
    if (key == NULL)
    {
        return false;
    }

    while (map != NULL)
    {
        int t = strcmp(key, map->key);
        if (t == 0)
        {
            return true;
        }
        if (t < 0)
        {
            map = map->leftChild;
            continue;
        }
        map = map->rightChild;
    }
    return false;
}

Map *mapPopLeast(Map *map, Map **leastPtr)
{
    if (leastPtr == NULL)
    {
        return map;
    }
    if (map == NULL || map->leftChild == NULL)
    {
        *leastPtr = NULL;
        return map;
    }
    if (map->leftChild->leftChild == NULL)
    {
        map->balance++;
        *leastPtr = map->leftChild;
        map->leftChild = NULL;
        return balance(map);
    }
    Balance prevChildBalance = map->leftChild->balance;
    map->leftChild = mapPopLeast(map->leftChild, leastPtr);
    Balance newChildBalance = map->leftChild->balance;
    if (!newChildBalance && prevChildBalance)
    {
        map->balance++;
    }
    return balance(map);
}

Map *mapPop(Map *map, char *key)
{
    if (map == NULL || key == NULL)
    {
        return NULL;
    }

    int t = strcmp(key, map->key);
    if (t == 0)
    {
        free(map->value);
        free(map->key);
        Map *rightChild = map->rightChild;
        if (rightChild == NULL)
        {
            return map->leftChild;
        }
        if (rightChild->leftChild == NULL)
        {
            rightChild->leftChild = map->leftChild;
            rightChild->balance = map->balance - 1;
            free(map);
            return rightChild;
        }
        Map *leastRightChild = NULL;
        Balance prevChildBalance = rightChild->balance;
        rightChild = mapPopLeast(rightChild, &leastRightChild);
        Balance newChildBalance = rightChild->balance;

        leastRightChild->balance = map->balance;
        if (!newChildBalance && prevChildBalance)
        {
            leastRightChild->balance--;
        }
        leastRightChild->leftChild = map->leftChild;
        leastRightChild->rightChild = rightChild;

        return balance(leastRightChild);
    }
    if (t < 0)
    {
        if (map->leftChild == NULL)
        {
            return map;
        }
        Balance prevChildBalance = map->leftChild->balance;
        map->leftChild = mapPop(map->leftChild, key);
        if (map->leftChild == NULL)
        {
            map->balance++;
            return balance(map);
        }
        Balance newChildBalance = map->leftChild->balance;
        if (!newChildBalance && prevChildBalance)
        {
            map->balance++;
        }
        return balance(map);
    }
    if (map->rightChild == NULL)
    {
        return map;
    }
    Balance prevChildBalance = map->rightChild->balance;
    map->rightChild = mapPop(map->rightChild, key);
    if (map->rightChild == NULL)
    {
        map->balance--;
        return balance(map);
    }
    Balance newChildBalance = map->rightChild->balance;
    if (!newChildBalance && prevChildBalance)
    {
        map->balance--;
    }
    return balance(map);
}

void mapFree(Map *map)
{
    if (map == NULL)
    {
        return;
    }
    free(map->key);
    free(map->value);
    mapFree(map->leftChild);
    mapFree(map->rightChild);
    free(map);
}