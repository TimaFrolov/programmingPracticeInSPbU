#pragma once

#include <stddef.h>
#include <stdio.h>

#include "errors.h"

typedef struct HashMap HashMap;

// Create hashMap
// Possible errors: MemoryAllocationError, GivenPointerIsNULL, OK
Error createHashMap(HashMap **hashMapPtr);

// Insert key-value pair into hashMap
// Possible errors: MemoryAllocationError, GivenPointerIsNULL, HashMapIsNULL, OK
Error hashMapInsert(HashMap *hashMap, char *key, size_t value);

// Get value from hashMap by key
// Possible errors: GivenPointerIsNULL, HashMapIsNULL, OK
Error hashMapGet(HashMap *hashMap, char *key, size_t _default, size_t *value);

// Pop key-value pair from hashMap
// Possible errors: GivenPointerIsNULL, HashMapIsNULL, OK
Error hashMapPop(HashMap *hashMap, char *key);

// Remove all elements from hashMap, use free(hashMap)
void hashMapFree(HashMap *hashMap);

// Print hashMap into stdout in format "<key> - <value>\n"
// Possible errors: HashMapIsNULL, OK
Error hashMapPrint(HashMap *hashMap);

// Print debug info of hashMap into stdout
// Possible errors: HashMapIsNULL, OK
Error hashMapPrintDebugInfo(HashMap *hashMap);