#include "stack.h"

#include <stdlib.h>
#include <string.h>

typedef struct StackElement
{
    void *value;
    struct StackElement *next;
} StackElement;

typedef struct Stack
{
    size_t elementSize;
    StackElement *top;
} Stack;

int createStack(Stack **stack, size_t elementSize)
{
    if (stack == NULL) {
        return -5;
    }
    if (elementSize == 0)
    {
        return -4;
    }
    *stack = calloc(1, sizeof(Stack));
    if (*stack == NULL)
    {
        return -1;
    }
    (*stack)->elementSize = elementSize;
    return 0;
}

int stackPush(Stack *stack, void *value)
{
    if (stack == NULL)
    {
        return -2;
    }
    if (stack->elementSize == 0)
    {
        return -4;
    }
    if (value == NULL)
    {
        return -5;
    }

    StackElement *newElement = calloc(1, sizeof(StackElement));
    void *_value = calloc(1, stack->elementSize);
    if (newElement == NULL || _value == NULL)
    {
        free(newElement);
        free(_value);
        return -1;
    }
    memcpy(_value, value, stack->elementSize);
    newElement->value = _value;
    newElement->next = stack->top;
    stack->top = newElement;
    return 0;
}

int stackPop(Stack *stack, void *value)
{
    if (stack == NULL)
    {
        return -2;
    }
    if (stack->top == NULL)
    {
        return -3;
    }
    if (stack->elementSize == 0)
    {
        return -4;
    }
    if (value == NULL)
    {
        return -5;
    }

    StackElement *topElement = stack->top;
    memcpy(value, topElement->value, stack->elementSize);
    stack->top = topElement->next;

    free(topElement->value);
    free(topElement);
    return 0;
}

int stackFree(Stack *stack)
{
    if (stack == NULL)
    {
        return -2;
    }

    StackElement *topElement = stack->top;
    while (topElement != NULL)
    {
        StackElement *nextElement = topElement->next;
        free(topElement->value);
        free(topElement);
        topElement = nextElement;
    }

    stack->top = NULL;
    return 0;
}

bool stackEmptyOrNULL(Stack *stack)
{
    return stack == NULL || stack->top == NULL;
}