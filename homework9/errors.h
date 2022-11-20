#pragma once

typedef enum Error {
    OK = 0,
    MemoryAllocationError = -1,
    ListIsNULL = -2,
    GivenIndexBiggerThanListLen = -3,
    ElementSizeIsZero = -4,
    GivenPointerIsNULL = -5,
    HashMapIsNULL = -6
} Error;