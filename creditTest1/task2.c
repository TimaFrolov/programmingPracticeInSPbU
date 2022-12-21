#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ubyte unsigned char

typedef enum
{
    OK,
    NoSuchFile = -1,
    MemoryAllocationError = -2,
    UnexpectedError = -3,
    IncorrectInput = -4
} Error;

typedef struct
{
    char *name;
    size_t amount;
} Product;

int compareByAmount(const void *product1, const void *product2)
{
    return (((Product *)product1)->amount < ((Product *)product2)->amount) - (((Product *)product1)->amount > ((Product *)product2)->amount);
}

int compareByName(const void *product1, const void *product2)
{
    return strcmp(((Product *)product1)->name, ((Product *)product2)->name);
}

void swap(Product *product1, Product *product2)
{
    Product tmp = *product1;
    *product1 = *product2;
    *product2 = tmp;
}

Error getNextNumber(size_t *number, FILE *file)
{
    *number = 0;
    int curChar = fgetc(file);
    while (curChar == '+' || curChar == ' ' || curChar == '\t')
    {
        curChar = fgetc(file);
    }
    ubyte charCounter = 0;
    while (curChar >= '0' && curChar <= '9' && charCounter <= 19)
    {
        *number = (*number * 10) + curChar - '0';
        curChar = fgetc(file);
        ++charCounter;
    }
    while (curChar == ' ' || curChar == '\t')
    {
        curChar = fgetc(file);
    }
    return (curChar == '\n' || curChar == EOF) ? OK : IncorrectInput;
}

Error getNextString(char **str, FILE *file)
{
    fpos_t curPosition;
    if (fgetpos(file, &curPosition) != 0)
    {
        return UnexpectedError;
    }
    size_t strLength = 0;
    for (int curChar = fgetc(file); curChar != '-'; curChar = fgetc(file))
    {
        if (curChar == '\n' || curChar == EOF)
        {
            return IncorrectInput;
        }
        ++strLength;
    }
    if (fsetpos(file, &curPosition) != 0)
    {
        return UnexpectedError;
    }
    *str = calloc(strLength + 1, sizeof(char));
    if (*str == NULL)
    {
        return MemoryAllocationError;
    }
    for (size_t i = 0; i < strLength; ++i)
    {
        (*str)[i] = fgetc(file);
    }
    fgetc(file);
    return OK;
}

Error getInputFromFile(Product **productsArrayPtr, size_t *productAmountPtr)
{
    FILE *file = fopen("storage.txt", "r");
    if (file == NULL)
    {
        return NoSuchFile;
    }

    *productAmountPtr = 1;
    fpos_t curPosition;
    if (fgetpos(file, &curPosition) != 0)
    {
        fclose(file);
        return UnexpectedError;
    }
    for (int curChar = fgetc(file); curChar != EOF; curChar = fgetc(file))
    {
        if (curChar == '\n')
        {
            ++*productAmountPtr;
        }
    }
    if (fsetpos(file, &curPosition) != 0)
    {
        fclose(file);
        return UnexpectedError;
    }

    Product *productsArray = calloc(*productAmountPtr, sizeof(Product));
    if (productsArray == NULL)
    {
        fclose(file);
        return MemoryAllocationError;
    }

    for (size_t i = 0; i < *productAmountPtr; ++i)
    {
        Error getStringError = getNextString(&productsArray[i].name, file);
        if (getStringError != OK)
        {
            fclose(file);
            for (size_t j = 0; j < i; ++j)
            {
                free(productsArray[j].name);
            }
            free(productsArray);
            return getStringError;
        }

        Error getNumberError = getNextNumber(&productsArray[i].amount, file);
        if (getNumberError != OK)
        {
            fclose(file);
            for (size_t j = 0; j <= i; ++j)
            {
                free(productsArray[j].name);
            }
            free(productsArray);
            return getNumberError;
        }
    }
    fclose(file);
    *productsArrayPtr = productsArray;
    return OK;
}

int main()
{
    size_t sale50PercentAmount;
    printf("Enter amount of products with 50%% sale: ");
    int scanResult = scanf("%lu", &sale50PercentAmount);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please enter number: ");
        scanResult = scanf("%lu", &sale50PercentAmount);
    }

    size_t sale25PercentAmount;
    printf("Enter amount of products with 25%% sale: ");
    scanResult = scanf("%lu", &sale25PercentAmount);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Incorrect input! Please enter number: ");
        scanResult = scanf("%lu", &sale25PercentAmount);
    }

    Product *productsArray;
    size_t productsAmount;
    Error fileReadError = getInputFromFile(&productsArray, &productsAmount);
    switch (fileReadError)
    {
    case NoSuchFile:
    {
        printf("Cannot open file storage.txt\n");
        return NoSuchFile;
    }
    case MemoryAllocationError:
    {
        printf("Error allocating memory!\n");
        return MemoryAllocationError;
    }
    case UnexpectedError:
    {
        printf("Unexpected error happened!\n");
        return UnexpectedError;
    }
    case IncorrectInput:
    {
        printf("Given file contains incorrect input!\n");
        return IncorrectInput;
    }
    case OK:
        break;
    }

    size_t logOfProductsAmount = 0;
    for (size_t i = 1; i < productsAmount && logOfProductsAmount <= 64; i <<= 1)
    {
        ++logOfProductsAmount;
    }

    if (sale50PercentAmount > logOfProductsAmount)
    {
        // works in O(productsAmount*log(productsAmount)) time
        qsort(productsArray, productsAmount, sizeof(Product), compareByAmount);
    }
    else
    {
        // works in O(productsAmount*sale50PercentAmount) time
        for (size_t i = 0; i < sale50PercentAmount; ++i)
        {
            Product *max = productsArray + i;
            for (size_t j = i + 1; j < productsAmount; ++j)
            {
                if (productsArray[j].amount > max->amount)
                {
                    max = productsArray + j;
                }
            }
            swap(max, productsArray + i);
        }
    }

    printf("Products with 50%% sale:\n");
    for (size_t i = 0; i < sale50PercentAmount; ++i)
    {
        printf("%s - %lu\n", productsArray[i].name, productsArray[i].amount);
    }

    if (sale25PercentAmount > logOfProductsAmount)
    {
        // works in O(productsAmount*log(productsAmount)) time
        qsort(productsArray + sale50PercentAmount, productsAmount - sale50PercentAmount, sizeof(Product), compareByName);
    }
    else
    {
        // works in O(productsAmount*sale25PercentAmount) time
        for (size_t i = sale50PercentAmount; i < sale50PercentAmount + sale25PercentAmount; ++i)
        {
            Product *min = productsArray + i;
            for (size_t j = i + 1; j < productsAmount; ++j)
            {
                if (strcmp(productsArray[j].name, min->name) < 0)
                {
                    min = productsArray + j;
                }
            }
            swap(min, productsArray + i);
        }
    }
    printf("Products with 25%% sale:\n");
    for (size_t i = sale50PercentAmount; i < sale50PercentAmount + sale25PercentAmount; ++i)
    {
        printf("%s - %lu\n", productsArray[i].name, productsArray[i].amount);
    }

    printf("Products without sale:\n");
    for (size_t i = sale50PercentAmount + sale25PercentAmount; i < productsAmount; ++i)
    {
        printf("%s - %lu\n", productsArray[i].name, productsArray[i].amount);
    }

    for (size_t i = 0; i < productsAmount; ++i)
    {
        free(productsArray[i].name);
    }
    free(productsArray);
    return 0;
}