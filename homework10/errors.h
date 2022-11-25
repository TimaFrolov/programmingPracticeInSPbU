#pragma once

typedef enum Error {
    OK = 0,
    MemoryAllocationError = -1,
    GivenPointerIsNULL = -2,
    QueueIsEmpty = -3
} Error;