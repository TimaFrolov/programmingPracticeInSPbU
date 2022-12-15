#include "stack.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct StackElement
{
    int value;
    struct StackElement *next;
} StackElement;

typedef struct Stack
{
    StackElement *top;
} Stack;

Error createStack(Stack **stack)
{
    if (stack == NULL)
    {
        return GivenPointerIsNULL;
    }
    *stack = calloc(1, sizeof(Stack));
    if (*stack == NULL)
    {
        return MemoryAllocationError;
    }
    return OK;
}

Error stackPush(Stack *stack, int value)
{
    if (stack == NULL)
    {
        return GivenPointerIsNULL;
    }
    StackElement *newElement = calloc(1, sizeof(StackElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }
    newElement->value = value;
    newElement->next = stack->top;
    stack->top = newElement;
    return OK;
}

Error stackPop(Stack *stack, int *value)
{
    if (stack == NULL || value == NULL)
    {
        return GivenPointerIsNULL;
    }
    if (stack->top == NULL)
    {
        return StackIsEmpty;
    }

    StackElement *topElement = stack->top;
    *value = topElement->value;
    stack->top = topElement->next;

    free(topElement);
    return OK;
}

Error stackFree(Stack *stack)
{
    if (stack == NULL)
    {
        return GivenPointerIsNULL;
    }

    StackElement *topElement = stack->top;
    while (topElement != NULL)
    {
        StackElement *nextElement = topElement->next;
        free(topElement);
        topElement = nextElement;
    }

    stack->top = NULL;
    return OK;
}

Error stackPrint(Stack *stack)
{
    if (stack == NULL)
    {
        return GivenPointerIsNULL;
    }

    StackElement *topElement = stack->top;
    while (topElement != NULL)
    {
        StackElement *nextElement = topElement->next;
        printf("%d ", topElement->value);
        topElement = nextElement;
    }

    return OK;
}
