#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef struct Stack Stack;

// Create stack, allocating for values elementSize bytes
// Error codes: -1 = error allocating memory, -4 = elementSize is 0, 0 = OK
int createStack(Stack **stack, size_t elementSize);

// Add an element to stack
// Error codes: -1 = error allocating memory, -2 = stack is NULL, -4 = elementSize is 0, -5 = value is NULL, 0 = OK
int stackPush(Stack *stack, void *value);

// Remove top element from stack, get it value
// Error codes: -2 = stack is NULL, -3 = stack is empty, -4 = elementSize is 0, -5 = value is NULL, 0 = OK
int stackPop(Stack *stack, void *value);

// Remove all elements from stack
// Error codes: -2 = stack is NULL, 0 = OK
int stackFree(Stack *stack);

// Returns true if stack is empty or stack is NULL
bool stackEmptyOrNULL(Stack *stack);