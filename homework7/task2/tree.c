#include "tree.h"

#include <stdlib.h>

typedef enum
{
    INT,
    CHAR
} ElementType;

typedef struct
{
    ElementType elementType;
    int value;
} Element;

typedef struct Tree
{
    Element value;
    Tree *leftChild, *rightChild;
} Tree;

Error createTreeFromFile(Tree **treePtr, FILE *file)
{
    if (file == NULL)
    {
        return FileIsNULL;
    }

    *treePtr = calloc(1, sizeof(Tree));
    if (*treePtr == NULL)
    {
        return MemoryAllocationError;
    }

    for (char c = getc(file); c != EOF; c = getc(file))
    {
        switch (c)
        {
        case '*':
        case '/':
        case '-':
        case '+':
        {
            (*treePtr)->value.elementType = CHAR;
            (*treePtr)->value.value = c;
            Tree *leftChild = NULL, *rightChild = NULL;
            Error errorCode1 = createTreeFromFile(&leftChild, file);
            Error errorCode2 = createTreeFromFile(&rightChild, file);
            if (errorCode1 != OK || errorCode2 != OK)
            {
                treeFree(leftChild);
                treeFree(rightChild);
                free(*treePtr);
                *treePtr = NULL;
                if (errorCode1 == IncorrectInput || errorCode2 == IncorrectInput)
                {
                    return IncorrectInput;
                }
                return MemoryAllocationError;
            }
            (*treePtr)->leftChild = leftChild;
            (*treePtr)->rightChild = rightChild;
            return OK;
        }
        default:
        {
            if (c < '0' || c > '9')
            {
                break;
            }
            ungetc(c, file);
            int num = 0;
            fscanf(file, "%d", &num);
            (*treePtr)->value.elementType = INT;
            (*treePtr)->value.value = num;
            return OK;
        }
        }
    }
    return IncorrectInput;
}

void treeFree(Tree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    treeFree(tree->leftChild);
    treeFree(tree->rightChild);
    free(tree);
}

void printTree(Tree *tree, FILE *file)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->value.elementType == INT)
    {
        printf("%d", tree->value.value);
        return;
    }

    fprintf(file, "( %c ", tree->value.value);
    printTree(tree->leftChild, file);
    fprintf(file, " ");
    printTree(tree->rightChild, file);
    fprintf(file, " )");
}

int evaluateTree(Tree *tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (tree->value.elementType == INT)
    {
        return tree->value.value;
    }
    switch (tree->value.value)
    {
    case '*':
    {
        return evaluateTree(tree->leftChild) * evaluateTree(tree->rightChild);
    }
    case '/':
    {
        return evaluateTree(tree->leftChild) / evaluateTree(tree->rightChild);
    }
    case '+':
    {
        return evaluateTree(tree->leftChild) + evaluateTree(tree->rightChild);
    }
    case '-':
    {
        return evaluateTree(tree->leftChild) - evaluateTree(tree->rightChild);
    }
    }

    return 0;
}