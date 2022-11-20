#include "hashMap.h"

#include "list.h"
#include <string.h>
#include <stdlib.h>

#define INITIAL_SIZE 16

typedef struct HashMap
{
    List **keys;
    List **values;
    size_t elementsAmount;
    size_t size;
} HashMap;

size_t hash(char *str)
{
    size_t ans = 0;
    for (; *str != 0; str++)
    {
        ans = ans * 13 + *str;
    }
    return ans;
}

bool compareKeys(void *key1, void *key2)
{
    return strcmp(*(char **)key1, *(char **)key2) == 0;
}

Error hashMapUpdateSize(HashMap *hashMap, size_t size)
{
    hashMap->keys = calloc(size, sizeof(List *));
    hashMap->values = calloc(size, sizeof(List *));
    if (hashMap->keys == NULL || hashMap->values == NULL)
    {
        free(hashMap->keys);
        free(hashMap->values);
        return MemoryAllocationError;
    }
    for (size_t i = 0; i < size; ++i)
    {
        Error keyCreationError = createList(hashMap->keys + i, sizeof(char *));
        Error valueCreationError = createList(hashMap->values + i, sizeof(size_t));
        if (keyCreationError == MemoryAllocationError || valueCreationError == MemoryAllocationError)
        {
            for (size_t j = 0; j <= i; ++j)
            {
                free(hashMap->keys[j]);
                free(hashMap->values[j]);
            }
            free(hashMap->keys);
            free(hashMap->values);
            return MemoryAllocationError;
        }
    }
    hashMap->size = size;
    return OK;
}

Error createHashMap(HashMap **hashMapPtr)
{
    if (hashMapPtr == NULL)
    {
        return GivenPointerIsNULL;
    }
    *hashMapPtr = calloc(1, sizeof(HashMap));
    if (*hashMapPtr == NULL)
    {
        return MemoryAllocationError;
    }
    Error fillError = hashMapUpdateSize(*hashMapPtr, INITIAL_SIZE);
    if (fillError == MemoryAllocationError)
    {
        free(*hashMapPtr);
        *hashMapPtr = NULL;
        return MemoryAllocationError;
    }

    return OK;
}

Error hashMapInsert(HashMap *hashMap, char *key, size_t value)
{
    if (hashMap == NULL)
    {
        return HashMapIsNULL;
    }
    if (key == NULL)
    {
        return GivenPointerIsNULL;
    }

    size_t keyHash = hash(key);
    size_t index = 0;
    bool notFound = true;
    listGetIndexOf(hashMap->keys[keyHash % hashMap->size], &key, &index, &notFound, compareKeys);
    if (!notFound)
    {
        listChangeValue(hashMap->values[keyHash % hashMap->size], index, &value);
        return OK;
    }
    ++(hashMap->elementsAmount);

    char *_key = calloc(strlen(key), sizeof(char));
    if (_key == NULL)
    {
        return MemoryAllocationError;
    }
    strcpy(_key, key);

    if (hashMap->elementsAmount < hashMap->size)
    {
        keyHash %= hashMap->size;
        Error keyAppendError = listAppend(hashMap->keys[keyHash], &_key);
        if (keyAppendError == MemoryAllocationError)
        {
            return MemoryAllocationError;
        }
        Error valueAppendError = listAppend(hashMap->values[keyHash], &value);
        if (valueAppendError == MemoryAllocationError)
        {
            return MemoryAllocationError;
        }
        return OK;
    }

    List **old_keys = hashMap->keys;
    List **old_values = hashMap->values;
    size_t old_size = hashMap->size;
    Error updateSizeError = hashMapUpdateSize(hashMap, hashMap->size * 2);
    if (updateSizeError == MemoryAllocationError)
    {
        hashMap->keys = old_keys;
        hashMap->values = old_values;
        hashMap->size = old_size;

        keyHash %= hashMap->size;
        Error keyAppendError = listAppend(hashMap->keys[keyHash], &_key);
        if (keyAppendError == MemoryAllocationError)
        {
            return MemoryAllocationError;
        }
        Error valueAppendError = listAppend(hashMap->values[keyHash], &value);
        if (valueAppendError == MemoryAllocationError)
        {
            return MemoryAllocationError;
        }
        return OK;
    }

    for (size_t i = 0; i < old_size; ++i)
    {
        size_t curListSize = 0;
        listLen(old_keys[i], &curListSize);
        for (size_t j = 0; j < curListSize; ++j)
        {
            char *curKey = NULL;
            size_t curValue = 0;
            listGet(old_keys[i], &curKey, j);
            listGet(old_values[i], &curValue, j);
            size_t curHash = hash(curKey) % hashMap->size;

            Error keyAppendError = listAppend(hashMap->keys[curHash], &curKey);
            if (keyAppendError == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
            Error valueAppendError = listAppend(hashMap->values[curHash], &curValue);
            if (valueAppendError == MemoryAllocationError)
            {
                return MemoryAllocationError;
            }
        }
        listFree(old_keys[i]);
        listFree(old_values[i]);
        free(old_keys[i]);
        free(old_values[i]);
    }
    free(old_keys);
    free(old_values);

    return OK;
}

Error hashMapGet(HashMap *hashMap, char *key, size_t _default, size_t *value)
{
    if (hashMap == NULL)
    {
        return HashMapIsNULL;
    }
    if (key == NULL || value == NULL)
    {
        return GivenPointerIsNULL;
    }

    size_t keyHash = hash(key) % hashMap->size;
    size_t index = 0;
    bool notFound = true;
    listGetIndexOf(hashMap->keys[keyHash], &key, &index, &notFound, compareKeys);

    if (notFound)
    {
        return _default;
    }

    listGet(hashMap->values[keyHash], value, index);
    return OK;
}

Error hashMapPop(HashMap *hashMap, char *key)
{
    if (hashMap == NULL)
    { 
        return HashMapIsNULL;
    }
    if (key == NULL)
    {
        return GivenPointerIsNULL;
    }

    size_t keyHash = hash(key) % hashMap->size;
    size_t index = 0;
    bool notFound = true;
    listGetIndexOf(hashMap->keys[keyHash], &key, &index, &notFound, compareKeys);

    if (notFound)
    {
        return OK;
    }

    listPop(hashMap->keys[keyHash], index);
    listPop(hashMap->values[keyHash], index);

    return OK;
}

void hashMapFree(HashMap *hashMap)
{
    if (hashMap == NULL)
    {
        return;
    }
    for (size_t i = 0; i < hashMap->size; ++i)
    {
        free(hashMap->keys[i]);
        free(hashMap->values[i]);
    }
    free(hashMap->keys);
    free(hashMap->values);
    free(hashMap);
}

Error hashMapPrint(HashMap *hashMap)
{
    if (hashMap == NULL)
    {
        return HashMapIsNULL;
    }

    for (size_t i = 0; i < hashMap->size; ++i)
    {
        size_t curListSize = 0;
        listLen(hashMap->keys[i], &curListSize);
        for (size_t j = 0; j < curListSize; ++j)
        {
            char *curKey = NULL;
            size_t curValue = 0;
            listGet(hashMap->keys[i], &curKey, j);
            listGet(hashMap->values[i], &curValue, j);

            printf("%s - %lu\n", curKey, curValue);
        }
    }

    return OK;
}

Error hashMapPrintDebugInfo(HashMap *hashMap)
{
    if (hashMap == NULL)
    {
        return HashMapIsNULL;
    }

    printf("Buckets count: %lu, elements count: %lu, fill factor: %.3f\n",
           hashMap->size, hashMap->elementsAmount, (float)hashMap->elementsAmount / hashMap->size);

    size_t bucketCount = 0;
    size_t maxBucketLength = 0;
    size_t sumBucketLength = 0;

    for (size_t i = 0; i < hashMap->size; ++i)
    {
        size_t curBucketLength = 0;
        listLen(hashMap->keys[i], &curBucketLength);
        if (curBucketLength > 0)
        {
            sumBucketLength += curBucketLength;
            ++bucketCount;
            if (curBucketLength > maxBucketLength)
            {
                maxBucketLength = curBucketLength;
            }
        }
    }

    printf("Max bucket length: %lu, average bucket length (for non-empty buckets): %.3f\n",
           maxBucketLength, (float)sumBucketLength / bucketCount);

    return OK;
}