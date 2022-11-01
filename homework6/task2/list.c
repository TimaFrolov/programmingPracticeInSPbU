#include "list.h"

#include <stdlib.h>

typedef struct ListElement
{
    int value;
    struct ListElement *prev;
    struct ListElement *next;
} ListElement;

typedef struct CyclicList
{
    ListElement *first;
} CyclicList;

Error createList(CyclicList **list)
{
    *list = calloc(1, sizeof(CyclicList));
    return (*list == NULL) ? MemoryAllocationError : OK;
}

Error listInsert(CyclicList *list, int value, int index)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }

    ListElement *newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }

    newElement->value = value;
    if (list->first == NULL)
    {
        list->first = newElement;
        newElement->prev = newElement->next = newElement;
        return OK;
    }

    if (list->first->next == list->first)
    {
        list->first->next = list->first->prev = newElement;
        newElement->prev = newElement->next = list->first;
        return OK;
    }

    ListElement *curElement = list->first;

    if (index > 0)
    {
        for (int i = 0; i < index; ++i)
        {
            curElement = curElement->next;
        }
        newElement->prev = curElement;
        newElement->next = curElement->next;
        curElement->next->prev = newElement;
        curElement->next = newElement;
        return OK;
    }

    for (int i = -1; i > index; --i)
    {
        curElement = curElement->prev;
    }
    newElement->next = curElement;
    newElement->prev = curElement->prev;
    curElement->prev->next = newElement;
    curElement->prev = newElement;
    return OK;
}

Error listRemoveEach(CyclicList *list, int first, int step, int amount)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (list->first == NULL)
    {
        return OK;
    }

    ListElement *curElement = list->first;

    if (first < 0)
    {
        for (int i = 0; i > first; --i)
        {
            curElement = curElement->prev;
        }
    }
    else
    {
        for (int i = 1; i < first; ++i)
        {
            curElement = curElement->next;
        }
    }

    while (amount--)
    {
        ListElement *nextElement = curElement->next;

        if (nextElement == curElement)
        {
            list->first = NULL;
            free(curElement);
            return OK;
        }

        curElement->prev->next = nextElement;
        nextElement->prev = curElement->prev;

        if (curElement == list->first)
        {
            list->first = nextElement;
        }

        free(curElement);
        curElement = nextElement;

        if (step < 0)
        {
            for (int i = 0; i > step; --i)
            {
                curElement = curElement->prev;
            }
        }
        else
        {
            for (int i = 1; i < step; ++i)
            {
                curElement = curElement->next;
            }
        }
    }

    return OK;
}

Error listGet(CyclicList *list, int *value, int index)
{
    if (list == NULL)
    {
        return ListIsNULL;
    }
    if (list->first == NULL)
    {
        return ListIsEmpty;
    }

    ListElement *curElement = list->first;

    if (index > 0)
    {
        for (int i = 0; i < index; ++i)
        {
            curElement = curElement->next;
        }
        *value = curElement->value;
        return OK;
    }

    for (int i = -1; i > index; --i)
    {
        curElement = curElement->prev;
    }
    *value = curElement->value;
    return OK;
}

Error listFree(CyclicList *list)
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

    list->first = NULL;

    return OK;
}