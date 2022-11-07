#pragma once

#include <stdio.h>

typedef enum
{
    OK = 0,
    MemoryAllocationError = -1,
    IncorrectInput = -2
} Error;

typedef struct Tree Tree;

// Create arithmetic expression parse tree from given file
// Possible errors: MemoryAllocationError, IncorrectInput, OK
Error createTreeFromFile(Tree **treePtr, FILE *file);

// Remove all elements from given tree, use free(tree)
void treeFree(Tree *tree);

// Print arithmetic expression parse tree to given file
void printTree(Tree *tree, FILE *file);

// Evaluate given arithmetic expression parse tree
int evaluateTree(Tree *tree);