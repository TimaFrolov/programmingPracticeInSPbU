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

int createList(List **list, size_t elementSize)
{
    if (list == NULL) {
        return -5;
    }
    if (elementSize == 0)
    {
        return -4;
    }
    *list = calloc(1, sizeof(List));
    if (*list == NULL)
    {
        return -1;
    }
    (*list)->elementSize = elementSize;
    return 0;
}

int listElementSize(List *list, size_t *elementSize)
{
    if (list == NULL)
    {
        return -2;
    }
    if (elementSize == NULL)
    {
        return -5;
    }
    *elementSize = list->elementSize;
    return 0;
}

int listAppend(List *list, void *value)
{
    if (list == NULL)
    {
        return -2;
    }
    if (value == NULL)
    {
        return -5;
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
    return 0;
}

int listPartition(List *list, List *sublist1, List *sublist2)
{
    if (list == NULL || sublist1 == NULL || sublist2 == NULL)
    {
        return -2;
    }
    if (list->elementSize != sublist1->elementSize || list->elementSize != sublist2->elementSize)
    {
        return -6;
    }
    if (sublist1->len != 0 || sublist2->len != 0)
    {
        return -7;
    }

    sublist1->first = list->first;

    ListElement *middle = list->first;
    for (size_t i = 1; i < list->len / 2; ++i)
    {
        middle = middle->next;
    }
    sublist1->last = middle;
    sublist2->first = middle->next;
    sublist2->last = (sublist2->first != NULL) ? list->last : NULL;

    sublist1->last->next = NULL;
    if (sublist2->first != NULL)
    {
        sublist2->first->prev = NULL;
    }
    sublist1->len = list->len / 2;
    sublist2->len = list->len - sublist1->len;
    list->len = 0;

    list->first = list->last = NULL;

    return 0;
}

int listMerge(List *sublist1, List *sublist2, List *list, bool (*compareFunction)(void *, void *))
{
    if (list == NULL || sublist1 == NULL || sublist2 == NULL)
    {
        return -2;
    }
    if (list->elementSize != sublist1->elementSize || list->elementSize != sublist2->elementSize)
    {
        return -6;
    }
    if (list->len != 0)
    {
        return -7;
    }

    ListElement *curElement1 = sublist1->first;
    ListElement *curElement2 = sublist2->first;

    ListElement *curElementNew = NULL;

    if (curElement1 != NULL && curElement2 != NULL)
    {
        if (compareFunction(curElement1->value, curElement2->value))
        {
            curElementNew = list->first = curElement1;
            curElement1 = curElement1->next;
        }
        else
        {
            curElementNew = list->first = curElement2;
            curElement2 = curElement2->next;
        }
    }

    while (curElement1 != NULL && curElement2 != NULL)
    {
        if (compareFunction(curElement1->value, curElement2->value))
        {
            curElementNew->next = curElement1;
            curElementNew = curElementNew->next;
            curElement1 = curElement1->next;
            continue;
        }
        curElementNew->next = curElement2;
        curElementNew = curElementNew->next;
        curElement2 = curElement2->next;
    }

    while (curElement1 != NULL)
    {
        curElementNew->next = curElement1;
        curElementNew = curElementNew->next;
        curElement1 = curElement1->next;
    }
    while (curElement2 != NULL)
    {
        curElementNew->next = curElement2;
        curElementNew = curElementNew->next;
        curElement2 = curElement2->next;
    }

    sublist1->first = sublist1->last = sublist2->first = sublist2->last = NULL;

    list->last = curElementNew;

    list->len = sublist1->len + sublist2->len;
    sublist1->len = sublist2->len = 0;

    return 0;
}

int listForEach(List *list, void (*function)(void *))
{
    if (list == NULL)
    {
        return -2;
    }

    ListElement *curElement = list->first;

    while (curElement != NULL)
    {
        function(curElement->value);
        curElement = curElement->next;
    }

    return 0;
}

int listLen(List *list, size_t *len)
{
    if (list == NULL)
    {
        return -2;
    }
    if (len == NULL)
    {
        return -5;
    }

    *len = list->len;

    return 0;
}

int listFree(List *list)
{
    if (list == NULL)
    {
        return -2;
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

    return 0;
}