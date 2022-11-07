#include <stdio.h>
#include "tree.h"

int main()
{
    char fileName[101] = {0};
    printf("Enter file path (no longer than 100 symbols): ");
    int scanResult = scanf("%s", fileName);
    while (scanResult == 0 || fileName[100] != 0)
    {
        printf("Incorrect input! Enter no more than 100 symbols: ");
        for (size_t i = 0; i < 101; ++i)
        {
            fileName[i] = 0;
        }
        scanResult = scanf("%s", fileName);
    }

    FILE *file = fopen(fileName, "r");
    Tree *tree;
    Error createResult = createTreeFromFile(&tree, file);
    if (createResult == MemoryAllocationError)
    {
        printf("Error allocating memory!\n");
        return -1;
    }
    if (createResult == IncorrectInput)
    {
        printf("Incorrect data in file!\n");
        return 0;
    }
    printf("Tree written from file: ");
    printTree(tree, stdout);
    printf("\nEvaluated value from this tree: %d\n", evaluateTree(tree));
    return 0;
}