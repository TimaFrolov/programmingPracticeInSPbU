#include <stdio.h>
#include "tree.h"

int main()
{
    char fileName[101] = {0};
    printf("Enter file path (no longer than 100 symbols): ");
    scanf("%100s", fileName);

    FILE *file = fopen(fileName, "r");
    Tree *tree;
    Error createResult = createTreeFromFile(&tree, file);

    switch (createResult)
    {
    case FileIsNULL:
    {
        printf("No such file!\n");
        return 0;
    }
    case MemoryAllocationError:
    {
        printf("Error allocating memory!\n");
        return -1;
    }
    case IncorrectInput:
    {
        printf("Incorrect data in file!\n");
        return 0;
    }
    }

    printf("Tree written from file: ");
    printTree(tree, stdout);
    printf("\nEvaluated value from this tree: %d\n", evaluateTree(tree));
    return 0;
}