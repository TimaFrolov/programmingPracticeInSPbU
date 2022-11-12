#include "list.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement
{
    int value;
    struct ListElement *next;
} ListElement;

typedef struct SortedList
{
    ListElement *top;
} SortedList;

int createList(SortedList **list)
{
    if (list == NULL) {
        return -2;
    }
    *list = calloc(1, sizeof(SortedList));
    return (list == NULL) ? -1 : 0;
}

int listAppend(SortedList *list, int value)
{
    if (list == NULL)
    {
        return -2;
    }

    ListElement *newElement = calloc(1, sizeof(ListElement));

    if (newElement == NULL)
    {
        return -1;
    }

    newElement->value = value;

    if (list->top == NULL)
    {
        list->top = newElement;
        return 0;
    }

    if (list->top->value > value)
    {
        newElement->next = list->top;
        list->top = newElement;
        return 0;
    }

    ListElement *maxLowerElement = list->top;

    while (maxLowerElement->next != NULL && maxLowerElement->next->value < value)
    {
        maxLowerElement = maxLowerElement->next;
    }

    newElement->next = maxLowerElement->next;
    maxLowerElement->next = newElement;

    return 0;
}

int listRemove(SortedList *list, int value)
{
    if (list == NULL)
    {
        return -2;
    }

    ListElement *curElement = list->top;

    if (curElement == NULL)
    {
        return 0;
    }

    while (curElement->next != NULL)
    {
        if (curElement->next->value == value)
        {
            ListElement *element = curElement->next;
            curElement->next = element->next;

            free(element);
            return 0;
        }
        curElement = curElement->next;
    }

    return 0;
};

int listPrint(SortedList *list)
{
    if (list == NULL)
    {
        return -2;
    }
    ListElement *curElement = list->top;

    printf("{");
    if (curElement == NULL)
    {
        printf("}");
        return 0;
    }

    printf("%d", curElement->value);
    curElement = curElement->next;

    while (curElement != NULL)
    {
        printf(", %d", curElement->value);
        curElement = curElement->next;
    }

    printf("}");
    return 0;
};

int listFree(SortedList *list)
{
    if (list == NULL)
    {
        return -2;
    }

    ListElement *curElement = list->top;
    while (curElement != NULL)
    {
        ListElement *nextElement = curElement->next;
        free(curElement);
        curElement = nextElement;
    }

    list->top = NULL;

    return 0;
}