#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct ListElement
{
    void *value;
    struct ListElement *prev, *next;
} ListElement;

typedef struct List
{
    size_t elementSize, len;
    ListElement *first, *last;
} List;

Error createList(List **list, size_t elementSize)
{
    if (list == NULL)
    {
        return GivenPointerIsNULL;
    }
    if (elementSize == 0)
    {
        return ElementSizeIsZero;
    }
    *list = calloc(1, sizeof(List));
    if (*list == NULL)
    {
        return MemoryAllocationError;
    }
    (*list)->elementSize = elementSize;
    return OK;
}

Error listElementSize(List *list, size_t *elementSize)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (elementSize == NULL)
    {
        return GivenPointerIsNULL;
    }
    *elementSize = list->elementSize;
    return OK;
}

Error listAppend(List *list, void *value)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (value == NULL)
    {
        return GivenPointerIsNULL;
    }

    ListElement *newElement = calloc(1, sizeof(ListElement));
    void *_value = calloc(1, list->elementSize);
    if (newElement == NULL || _value == NULL)
    {
        free(newElement);
        free(_value);
        return -1;
    }
    memcpy(_value, value, list->elementSize);
    newElement->value = _value;
    newElement->prev = list->last;
    newElement->next = NULL;
    if (list->last != NULL)
    {
        list->last->next = newElement;
    }
    list->last = newElement;
    if (list->first == NULL)
    {
        list->first = newElement;
    }
    ++(list->len);
    return OK;
}

Error listLen(List *list, size_t *len)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (len == NULL)
    {
        return GivenPointerIsNULL;
    }

    *len = list->len;

    return OK;
}

Error listFree(List *list)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }

    ListElement *curElement = list->first;

    while (curElement != NULL && curElement != list->first)
    {
        ListElement *nextElement = curElement->next;
        free(curElement);
        curElement = nextElement;
    }

    list->first = list->last = NULL;
    list->len = 0;

    return OK;
}

Error listGetIndexOf(List *list, void *value, size_t *index, bool *notFound, bool (*compareFunction)(void *, void *))
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (value == NULL || index == NULL || notFound == NULL)
    {
        return GivenPointerIsNULL;
    }

    ListElement *curElement = list->first;

    for (size_t i = 0; i < list->len; ++i)
    {
        if (compareFunction(curElement->value, value))
        {
            *notFound = false;
            *index = i;
            return OK;
        }
        curElement = curElement->next;
    }

    *notFound = true;
    *index = 0;
    return OK;
}

Error listGet(List *list, void *value, size_t index)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (value == NULL)
    {
        return GivenPointerIsNULL;
    }

    ListElement *curElement = list->first;
    for (size_t i = 0; i < index; ++i)
    {
        if (curElement == NULL)
        {
            return GivenIndexBiggerThanListLen;
        }
        curElement = curElement->next;
    }

    if (curElement == NULL)
    {
        return GivenIndexBiggerThanListLen;
    }

    memcpy(value, curElement->value, list->elementSize);
    return OK;
}

Error listPop(List *list, size_t index)
{

    if (list == NULL)
    {
        return ListIsNULL;
    }

    ListElement *curElement = list->first;
    for (size_t i = 0; i < index; ++i)
    {
        if (curElement == NULL)
        {
            return GivenIndexBiggerThanListLen;
        }
        curElement = curElement->next;
    }

    if (curElement == NULL)
    {
        return GivenIndexBiggerThanListLen;
    }

    if (curElement == list->first)
    {
        list->first = curElement->next;
    }
    if (curElement == list->last)
    {
        list->last = curElement->prev;
    }
    if (curElement->next != NULL)
    {
        curElement->next->prev = curElement->prev;
    }
    if (curElement->prev != NULL)
    {
        curElement->prev->next = curElement->next;
    }

    free(curElement->value);
    free(curElement);

    --(list->len);

    return OK;
}

Error listChangeValue(List *list, size_t index, void *value)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (value == NULL)
    {
        return GivenPointerIsNULL;
    }

    ListElement *curElement = list->first;
    for (size_t i = 0; i < index; ++i)
    {
        if (curElement == NULL)
        {
            return GivenIndexBiggerThanListLen;
        }
        curElement = curElement->next;
    }

    if (curElement == NULL)
    {
        return GivenIndexBiggerThanListLen;
    }

    memcpy(curElement->value, value, list->elementSize);
    return OK;
}