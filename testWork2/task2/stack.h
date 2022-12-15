#pragma once


typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    GivenPointerIsNULL = -2,
    StackIsEmpty = -3,
} Error;

typedef struct Stack Stack;

// Create stack, allocating for values elementSize bytes
// Possible errors: MemoryAllocationErrors, GivenPointerIsNULL, OK
Error createStack(Stack **stack);

// Add an element to stack
// Possible errors: MemoryAllocationErrors, GivenPointerIsNULL, OK
Error stackPush(Stack *stack, int value);

// Remove top element from stack, get it value
// Possible errors: GivenPointerIsNULL, StackIsEmpty, OK
Error stackPop(Stack *stack, int *value);

// Remove all elements from stack
// Possible errors: GivenPointerIsNULL, OK
Error stackFree(Stack *stack);

// Print stack into stdin
// Possible errors: GivenPointerIsNULL, OK
Error stackPrint(Stack *stack);