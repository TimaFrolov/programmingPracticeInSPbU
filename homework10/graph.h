#pragma once

#include <stddef.h>
#include "errors.h"

typedef struct Graph Graph;

Error createGraph(Graph **graphPtr, unsigned int size);

void graphSet(Graph *graph, unsigned int first, unsigned int second, size_t len);

void graphCalculate(Graph *graph);

size_t graphGet(Graph *graph, unsigned int first, unsigned int second);

void graphFree(Graph *graph);

void graphPrint(Graph *graph);