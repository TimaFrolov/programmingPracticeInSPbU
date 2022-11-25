#pragma once

#include "errors.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct HashSet HashSet;

//
// Possible errors:
Error createHashSet(HashSet **hashSetPtr);

//s
// Possible errors:
Error hashSetInsert(HashSet *hashSet, size_t key);

//
bool hashSetContains(HashSet *hashSet, size_t key);

//
void hashSetRemove(HashSet *hashSet, size_t key);