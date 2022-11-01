#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct List List;

// Create list, allocating for values elementSize bytes
// Error codes: -1 = error allocating memory, -4 = elementSize is 0, 0 = OK
int createList(List **list, size_t elementSize);

// Put size of element of <list> to <elementSize>
// Error codes: -2 = <list> is NULL, -5 = <elementSize> is NULL, 0 = OK
int listElementSize(List *list, size_t *elementSize);

// Add an element to list
// Error codes: -1 = error allocating memory, -2 = list is NULL, -4 = elementSize is 0, -5 = value is NULL, 0 = OK
int listAppend(List *list, void *value);

// Divide list into two sublists
// <list> becomes empty list (with no elements and 0 length)
// Error codes: -2 = one of given lists is NULL, -6 = elementSize of lists doesn't equal, -7 = one of sublists is not empty, 0 = OK
int listPartition(List *list, List *sublist1, List *sublist2);

// Merge two sorted list into sorted list
// compareFunction has to return true if first argument <= then second argument else false
// Error codes: -2 = one of given lists is NULL, -6 = elementSize of lists doesn't equal, -7 = <list> is not empty, 0 = OK
int listMerge(List *sublist1, List *sublist2, List *list, bool (*compareFunction)(void *, void *));

// Execute given function for every element of list
// Error codes: -2 = <list> is NULL, 0 = OK
int listForEach(List *list, void (*function)(void *));

// Put length of <list> to <len>
// Error codes: -2 = <list> is NULL, -5 = <len> is NULL, 0 = OK
int listLen(List *list, size_t *len);

// Remove every element from list
// Error codes: -2 = <list> is NULL, 0 = OK
int listFree(List *list);