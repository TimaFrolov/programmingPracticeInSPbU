#include "queue.h"
#include <stdlib.h>

typedef struct QueueElement
{
    size_t value;
    struct QueueElement *next;
} QueueElement;

typedef struct Queue
{
    QueueElement *head;
    QueueElement *tail;
} Queue;

Error createQueue(Queue **queuePtr)
{
    if (queuePtr == NULL)
    {
        return GivenPointerIsNULL;
    }

    *queuePtr = calloc(1, sizeof(Queue));
    if (*queuePtr == NULL)
    {
        return MemoryAllocationError;
    }

    return OK;
}

Error queuePush(Queue *queue, size_t value)
{
    if (queue == NULL)
    {
        return GivenPointerIsNULL;
    }

    QueueElement *newElement = calloc(1, sizeof(QueueElement));
    if (newElement == NULL)
    {
        return MemoryAllocationError;
    }
    newElement->value = value;

    if (queue->head == NULL)
    {
        queue->head = newElement;
        queue->tail = newElement;
        return OK;
    }

    queue->head->next = newElement;
    queue->head = newElement;
    return OK;
}

Error queuePop(Queue *queue, size_t *valuePtr)
{
    if (queue == NULL || valuePtr == NULL)
    {
        return GivenPointerIsNULL;
    }

    if (queue->tail == NULL)
    {
        return QueueIsEmpty;
    }

    *valuePtr = queue->tail->value;
    QueueElement *newTail = queue->tail->next;
    free(queue->tail);
    queue->tail = newTail;
    return OK;
}