#include "map.h"

#include <stdlib.h>
#include <string.h>

typedef struct Map
{
    int key;
    char *value;
    struct Map *leftChild, *rightChild;
} Map;

Map *createMap()
{
    return NULL;
}

Error mapInsert(Map **mapPtr, int key, char *value)
{
    if (*mapPtr == NULL)
    {
        *mapPtr = calloc(1, sizeof(Map));
        if (*mapPtr == NULL)
        {
            return MemoryAllocationError;
        }

        (*mapPtr)->value = calloc(strlen(value) + 1, sizeof(char));
        if ((*mapPtr)->value == NULL)
        {
            free(*mapPtr);
            *mapPtr = NULL;
            return MemoryAllocationError;
        }

        (*mapPtr)->key = key;
        strcpy((*mapPtr)->value, value);

        return OK;
    }

    Map *map = *mapPtr;

    while (map->leftChild != NULL || map->rightChild != NULL)
    {
        if (key == map->key)
        {
            char *val = calloc(strlen(value) + 1, sizeof(char));
            if (val == NULL)
            {
                return MemoryAllocationError;
            }
            free(map->value);
            strcpy(val, value);
            map->value = val;
            return OK;
        }
        if (key < map->key)
        {
            if (map->leftChild == NULL)
            {
                break;
            }
            map = map->leftChild;
            continue;
        }
        if (map->rightChild == NULL)
        {
            break;
        }
        map = map->rightChild;
    }

    char *val = calloc(strlen(value) + 1, sizeof(char));
    if (val == NULL)
    {
        return MemoryAllocationError;
    }
    strcpy(val, value);

    if (key == map->key)
    {
        free(map->value);
        map->value = val;
        return OK;
    }

    Map *newNode = calloc(1, sizeof(Map));
    if (newNode == NULL)
    {
        return MemoryAllocationError;
    }
    newNode->key = key;
    newNode->value = val;

    if (key < map->key)
    {
        map->leftChild = newNode;
        return OK;
    }
    map->rightChild = newNode;
    return OK;
}

Error mapGet(Map *map, int key, char **value)
{
    while (map != NULL)
    {
        if (key == map->key)
        {
            char *val = calloc(strlen(map->value) + 1, sizeof(char));
            if (val == NULL)
            {
                return MemoryAllocationError;
            }
            strcpy(val, map->value);
            *value = val;
            return OK;
        }
        if (key < map->key)
        {
            map = map->leftChild;
            continue;
        }
        map = map->rightChild;
    }
    *value = NULL;
    return OK;
}

bool mapContains(Map *map, int key)
{
    while (map != NULL)
    {
        if (key == map->key)
        {
            return true;
        }
        if (key < map->key)
        {
            map = map->leftChild;
            continue;
        }
        map = map->rightChild;
    }
    return false;
}

// side: 0=left, 1=right
void removeChild(Map *parent, bool side)
{
    if (parent == NULL)
    {
        return;
    }
    Map *child = side ? parent->rightChild : parent->leftChild;

    if (child == NULL)
    {
        return;
    }

    Map *childOfChild = child->rightChild;

    if (childOfChild == NULL)
    {
        parent->rightChild = child->leftChild;
        free(child->value);
        free(child);
        return;
    }
    if (childOfChild->leftChild == NULL)
    {
        childOfChild->leftChild = child->leftChild;
        parent->rightChild = childOfChild;
        free(child->value);
        free(child);
        return;
    }
    while (childOfChild->leftChild != NULL && childOfChild->leftChild->leftChild != NULL)
    {
        childOfChild = childOfChild->leftChild;
    }

    Map *leftChildOfChildOfChild = childOfChild->leftChild;

    child->key = leftChildOfChildOfChild->key;
    child->value = leftChildOfChildOfChild->value;

    childOfChild = leftChildOfChildOfChild->rightChild;

    free(leftChildOfChildOfChild);
}

void mapPop(Map *map, int key)
{
    while (map != NULL)
    {
        if (key < map->key)
        {
            if (map->leftChild == NULL)
            {
                return;
            }
            if (map->leftChild->key == key)
            {
                removeChild(map, 0);
                return;
            }
            map = map->leftChild;
            continue;
        }

        if (map->rightChild == NULL)
        {
            return;
        }
        if (map->rightChild->key == key)
        {
            removeChild(map, 0);
            return;
        }
        map = map->rightChild;
    }
    return;
}

void mapFree(Map *map)
{
    if (map == NULL)
    {
        return;
    }
    free(map->value);
    mapFree(map->leftChild);
    mapFree(map->rightChild);
    free(map);
}