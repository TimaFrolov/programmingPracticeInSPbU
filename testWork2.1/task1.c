#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 4096
#define uint unsigned int
#define ubyte unsigned char

typedef enum
{
    OK,
    IncorrectInput,
    EndOfFile
} Error;

typedef struct
{
    uint amount;
    uint cost;
} Product;

// Return last read character, place read number to <number>
int getNextNumber(uint *number, FILE *stream)
{
    *number = 0;
    int curChar = fgetc(stream);
    if (curChar == '+')
    {
        curChar = fgetc(stream);
    }
    ubyte charCounter = 0;
    while (curChar >= '0' && curChar <= '9' && charCounter <= 8)
    {
        *number = (*number * 10) + curChar - '0';
        curChar = fgetc(stream);
        ++charCounter;
    }
    return curChar;
}

Error getNextProduct(Product *product, FILE *stream)
{
    int curChar = fgetc(stream);
    if (curChar == EOF)
    {
        return EndOfFile;
    }

    // Skip name
    while (curChar != '\t' && curChar != '\n' && curChar != EOF)
    {
        curChar = fgetc(stream);
    }
    if (curChar != '\t')
    {
        return IncorrectInput;
    }

    // Read amount
    curChar = getNextNumber(&product->amount, stream);
    if (curChar != '\t')
    {
        return IncorrectInput;
    }

    // Read cost
    curChar = getNextNumber(&product->cost, stream);
    if (curChar != '\n' && curChar != EOF)
    {
        return IncorrectInput;
    }

    return OK;
}

int main()
{
    char filepath[PATH_MAX] = {'\0'};
    printf("Enter file path (no longer than %d symbols): ", PATH_MAX);
    scanf("%s", filepath);
    if (filepath[PATH_MAX - 1] != '\0')
    {
        printf("Given file path is too long!\n");
        return -3;
    }
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Cannot open file on given path!\n");
        return -4;
    }

    Product product = {amount : 0, cost : 0};

    uint totalCost = 0;
    Error readError = getNextProduct(&product, file);
    while (readError == OK)
    {
        totalCost += product.amount * product.cost;
        readError = getNextProduct(&product, file);
    }

    if (readError == IncorrectInput)
    {
        printf("Given file contains incorrect data!\n");
        return -2;
    }

    printf("Total cost of order: %u\n", totalCost);
    return 0;
}