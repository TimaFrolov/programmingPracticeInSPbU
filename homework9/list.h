#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "errors.h"

typedef struct List List;

// Create list, allocating for values <elementSize> bytes
// Possible errors: MemoryAllocationError, ElementSizeIsZero, GivenPointerIsNULL, OK
Error createList(List **list, size_t elementSize);

// Put size of element of <list> to <elementSize>
// Possible errors: ListIsNULL, GivenPointerIsNULL, OK
Error listElementSize(List *list, size_t *elementSize);

// Add an element to <list>
// Possible errors: MemoryAllocationError, ListIsNULL, GivenPointerIsNULL, OK
Error listAppend(List *list, void *value);

// Put length of <list> to <len>
// Possible errors: ListIsNULL, GivenPointerIsNULL, OK
Error listLen(List *list, size_t *len);

// Remove every element from <list>
// Possible erros: ListIsNULL, OK
Error listFree(List *list);

// Get index of element, which is `equal` to <value>, comparing using <compareFunction>
// compareFunction should return true if first argument equal to second argument else false
// Possible errors: ListIsNULL, GivenPointerIsNULL, OK
Error listGetIndexOf(List *list, void *value, size_t *index, bool *notFound, bool (*compareFunction)(void *, void *));

// Get element from <list> at given <index>
// Possible errors: ListIsNULL, GivenIndexBiggerThanListLen, GivenPointerIsNULL, OK
Error listGet(List *list, void *value, size_t index);

// Remove element from <list> at given <index>
// Possible errors: ListIsNULL, GivenIndexBiggerThanListLen, OK
Error listPop(List *list, size_t index);

// Change <value> for element in <list> at given <index>
// Possible errors: ListIsNULL, GivenIndexBiggerThanListLen, GivenPointerIsNULL, OK
Error listChangeValue(List *list, size_t index, void *value);