#include <stddef.h>

typedef enum Error
{
    OK = 0,
    MemoryAllocationError = -1,
    ListIsNULL = -2,
    ListIsEmpty = -3
} Error;

typedef struct CyclicList CyclicList;

// Create cyclic list of integers
// Possible errors: MemoryAllocationError
Error createList(CyclicList **list);

// Insert <value> to list at <index>
// Possible errors: MemoryAllocationError, ListIsNULL
Error listInsert(CyclicList *list, int value, int index);

// Remove <amount> values from list with given <step>, starting from <first>
// If list contains less than <amount> elements, remove all of them
// Possible errors: ListIsNULL
Error listRemoveEach(CyclicList *list, int first, int step, int amount);

// Copy value from list at <index> to <value>
// Possible errors: ListIsNULL, ListIsEmpty
Error listGet(CyclicList *list, int *value, int index);

// Remove all elements from list
// Possible errors: ListIsNULL
Error listFree(CyclicList *list);