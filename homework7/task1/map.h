#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1
} Error;

typedef struct Map Map;

// Create map of strings by integers
Map *createMap();

// Insert given <value> by given <key> in given <mapPtr>
// Possible errors: MemoryAllocationError, OK
Error mapInsert(Map **mapPtr, int key, char *value);

// Put value by given <key> in <value> from <map>
// Possible errors: MemoryAllocationError, OK
Error mapGet(Map *map, int key, char **value);

// Check if <map> has <key> in it
bool mapContains(Map *map, int key);

// Remove given <key> from <map>
void mapPop(Map *map, int key);

// Remove all keys from <map>, use free(map)
void mapFree(Map *map);