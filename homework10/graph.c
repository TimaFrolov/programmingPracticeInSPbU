#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#define uint unsigned int

typedef struct Graph
{
    size_t *table;
    uint size;
    size_t tableSize;
} Graph;

Error createGraph(Graph **graphPtr, uint size)
{
    if (graphPtr == NULL)
    {
        return GivenPointerIsNULL;
    }

    *graphPtr = calloc(1, sizeof(Graph));
    if (*graphPtr == NULL)
    {
        return MemoryAllocationError;
    }

    (*graphPtr)->tableSize = (size_t)size * (size - 1) / 2;

    (*graphPtr)->table = calloc((*graphPtr)->tableSize, sizeof(size_t));
    if ((*graphPtr)->table == NULL)
    {
        free(*graphPtr);
        *graphPtr = NULL;
        return MemoryAllocationError;
    }

    for (size_t i = 0; i < (*graphPtr)->tableSize; ++i)
    {
        (*graphPtr)->table[i] = __UINT64_MAX__;
    }

    (*graphPtr)->size = size;

    return OK;
}

void swap(uint *a, uint *b)
{
    *a = *a ^ *b; // a = a ^ b
    *b = *a ^ *b; // b = (a ^ b) ^ b = a
    *a = *a ^ *b; // a = (a ^ b) ^ a = b
}

void graphSet(Graph *graph, uint first, uint second, size_t len)
{
    if (graph == NULL || first == second)
    {
        return;
    }
    if (first < second)
    {
        swap(&first, &second);
    }

    size_t pos = (size_t)first * (first - 1) / 2 + second;
    if (pos < graph->tableSize)
    {
        graph->table[pos] = len;
    }
}

size_t graphGet(Graph *graph, uint first, uint second)
{
    if (graph == NULL || first == second)
    {
        return 0;
    }
    if (first < second)
    {
        swap(&first, &second);
    }

    size_t pos = (size_t)first * (first - 1) / 2 + second;
    if (pos < graph->tableSize)
        return graph->table[pos];
    return __UINT64_MAX__;
}

void graphCalculate(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }
    for (uint k = 0; k < graph->size; ++k)
    {
        for (uint i = 0; i < graph->size; ++i)
        {
            for (uint j = 0; j < graph->size; ++j)
            {
                size_t a = graphGet(graph, i, j);
                size_t b = graphGet(graph, i, k);
                size_t c = graphGet(graph, k, j);

                if (b == __UINT64_MAX__ || c == __UINT64_MAX__)
                {
                    continue;
                }

                if (a > b + c)
                {
                    graphSet(graph, i, j, b + c);
                }
            }
        }
    }
}

void graphFree(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }
    free(graph->table);
    free(graph);
}

void graphPrint(Graph *graph)
{
    if (graph == NULL)
    {
        return;
    }

    printf("  |");
    for (uint i = 0; i < graph->size; ++i)
    {
        printf(" %u", i);
    }
    printf("\n");

    for (uint i = 0; i < graph->size; ++i)
    {
        printf("%u |", i);
        for (uint j = 0; j < graph->size; ++j)
        {
            printf(" %lu", graphGet(graph, i, j));
        }
        printf("\n");
    }
}