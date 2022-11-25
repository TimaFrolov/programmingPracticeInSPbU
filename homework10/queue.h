#pragma once

#include "errors.h"
#include <stddef.h>

typedef struct Queue Queue;

//
// Possible errors:
Error createQueue(Queue **queuePtr);

//s
// Possible errors:
Error queuePush(Queue *queue, size_t value);

//
Error queuePop(Queue *queue, size_t *valuePtr);
