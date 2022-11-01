#include "list.h"

// Sort <list> using <compareFunction>
// compareFunction has to return true if first argument <= then second argument else false
// Returns true if succesfully sorted, false if error occured due to execution
bool msort(List *list, bool (*compareFunction)(void *, void *));