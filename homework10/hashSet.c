#include "hashSet.h"
#include <stdlib.h>

#define INITIAL_SIZE 16

typedef enum Status
{
    FREE = 0,
    OCCUPIED,
    WAS_OCCUPIED,
} Status;

typedef struct HashSetELement
{
    size_t key;
    Status status;
} HashSetElement;

typedef struct HashSet
{
    HashSetElement *keys;
    size_t size;
    size_t elementsAmount;
} HashSet;

Error createHashSet(HashSet **hashSetPtr)
{
    if (hashSetPtr == NULL)
    {
        return GivenPointerIsNULL;
    }

    *hashSetPtr = calloc(1, sizeof(HashSet));
    if (*hashSetPtr == NULL)
    {
        return MemoryAllocationError;
    }

    (*hashSetPtr)->keys = calloc(INITIAL_SIZE, sizeof(HashSetElement));
    if ((*hashSetPtr)->keys == NULL)
    {
        free(*hashSetPtr);
        *hashSetPtr = NULL;
        return MemoryAllocationError;
    }
    (*hashSetPtr)->size = INITIAL_SIZE;

    return OK;
}

Error hashSetResize(HashSet *hashSet)
{
    if (hashSet == NULL)
    {
        return GivenPointerIsNULL;
    }

    hashSet->size = hashSet->size * 2;
    HashSetElement *newKeys = calloc(hashSet->size, sizeof(HashSetElement));
    if (newKeys == NULL)
    {
        return MemoryAllocationError;
    }

    for (size_t i = 0; i < hashSet->size; i++)
    {
        if (hashSet->keys[i].status == OCCUPIED)
        {
            size_t hash = hashSet->keys[i].key % hashSet->size;
            while (newKeys[hash].status == OCCUPIED)
            {
                hash = (hash + 1) % hashSet->size;
            }
            newKeys[hash].key = hashSet->keys[i].key;
            newKeys[hash].status = OCCUPIED;
        }
    }

    free(hashSet->keys);
    hashSet->keys = newKeys;

    return OK;
}

Error hashSetInsert(HashSet *hashSet, size_t key)
{
    if (hashSet == NULL)
    {
        return GivenPointerIsNULL;
    }

    if (hashSet->elementsAmount >= hashSet->size / 2)
    {
        Error error = hashSetResize(hashSet);
        if (error != OK)
        {
            return error;
        }
    }

    size_t hash = key % hashSet->size;
    while (hashSet->keys[hash].status == OCCUPIED)
    {
        if (hashSet->keys[hash].key == key)
        {
            return OK;
        }
        hash = (hash + 1) % hashSet->size;
    }

    hashSet->keys[hash].key = key;
    hashSet->keys[hash].status = OCCUPIED;
    hashSet->elementsAmount++;

    return OK;
}

bool hashSetContains(HashSet *hashSet, size_t key)
{
    if (hashSet == NULL)
    {
        return false;
    }

    size_t hash = key % hashSet->size;
    while (hashSet->keys[hash].status != FREE)
    {
        if (hashSet->keys[hash].status == OCCUPIED && hashSet->keys[hash].key == key)
        {
            return true;
        }
        hash = (hash + 1) % hashSet->size;
    }

    return false;
}

void hashSetRemove(HashSet *hashSet, size_t key)
{
    if (hashSet == NULL)
    {
        return;
    }

    size_t hash = key % hashSet->size;
    while (hashSet->keys[hash].status != FREE)
    {
        if (hashSet->keys[hash].status == OCCUPIED && hashSet->keys[hash].key == key)
        {
            hashSet->keys[hash].status = WAS_OCCUPIED;
            hashSet->elementsAmount--;
            return;
        }
        hash = (hash + 1) % hashSet->size;
    }
}