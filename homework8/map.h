#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    GivenCharPointerIsNULL = -2
} Error;

typedef struct Map Map;

// Creates a new ordered map.
// Returns NULL if memory allocation failed.
Map *createMap();

// Insert given <value> by given <key> in given <mapPtr>
// Possible errors: MemoryAllocationError, OK
Error mapInsert(Map **mapPtr, char *key, char *value);

// Put value by given <key> in <value> from <map>
// Possible errors: MemoryAllocationError, OK
Error mapGet(Map *map, char *key, char **value);

// Check if <map> has <key> in it
bool mapContains(Map *map, char *key);

// Remove given <key> from <map>
Map *mapPop(Map *map, char *key);

// Remove all keys from <map>, use free(map)
void mapFree(Map *map);