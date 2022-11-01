#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct SortedList SortedList;

// Create ordered list of integers
// Error codes: -1 = error allocating memory, 0 = OK
int createList(SortedList **list);

// Append element to list
// Error codes: -1 = error allocating memory, -2 = list is NULL, 0 = OK
int listAppend(SortedList *list, int value);

// Remove element from list
// Error codes: -2 = list is NULL, 0 = OK
int listRemove(SortedList *list, int value);

// Print list to stdout
// Error codes: -2 = list is NULL, 0 = OK
int listPrint(SortedList *list);

// Remove all elements from list
// Error codes: -2 = list is NULL, 0 = OK
int listFree(SortedList *list);