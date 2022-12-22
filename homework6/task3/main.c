#include <stdio.h>
#include "list.h"
#include "msort.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char phoneNumber[16];
    char name[51];
} Record;

bool compareByPhoneNumber(void *a, void *b)
{
    return strcmp(((Record *)a)->phoneNumber, ((Record *)b)->phoneNumber) <= 0;
}

bool compareByName(void *a, void *b)
{
    return strcmp(((Record *)a)->name, ((Record *)b)->name) <= 0;
}

void printRecord(void *record)
{
    printf("%s - %s\n", ((Record *)record)->phoneNumber, ((Record *)record)->name);
}

signed char readCommand()
{
    printf("Input command (0 - exit, 1 - sort database by phoneNumber, 2 - sort database by name, 3 - print database): ");
    signed char command = -1;
    int scanResult = scanf("%hhi", &command);
    while (scanResult == 0 || command > 3 || command < 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please try again: ");
        scanResult = scanf("%hhi", &command);
    }
    return command;
}

int readDataFromFile(List *list, char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -3;
    }

    Record *tempRecord = calloc(1, sizeof(Record));
    if (tempRecord == NULL)
    {
        return -1;
    }
    size_t currentIndex = 0;
    bool wasDash = false;

    for (char c = getc(file); c != EOF; c = getc(file))
    {
        switch (c)
        {
        case '-':
        {
            if (wasDash)
            {
                free(tempRecord);
                fclose(file);
                return -4;
            }
            currentIndex = 0;
            wasDash = true;
            break;
        }
        case EOF:
        case '\n':
        {
            if (currentIndex > 0 && wasDash)
            {
                int errorCode = listAppend(list, tempRecord);
                if (errorCode == -1)
                {
                    free(tempRecord);
                    fclose(file);
                    return -1;
                }
            }
            currentIndex = 0;
            wasDash = false;
            for (size_t i = 0; i < 16; ++i)
            {
                tempRecord->phoneNumber[i] = '\0';
            }
            for (size_t i = 0; i < 51; ++i)
            {
                tempRecord->name[i] = '\0';
            }
            break;
        }
        default:
        {
            if (currentIndex > 50 || (!wasDash && currentIndex > 15))
            {
                free(tempRecord);
                free(file);
                return -4;
            }
            if (wasDash)
            {
                tempRecord->name[currentIndex] = c;
                ++currentIndex;
                break;
            }
            tempRecord->phoneNumber[currentIndex] = c;
            ++currentIndex;
            break;
        }
        }
    }

    int errorCode = 0;

    if (currentIndex > 0 && wasDash)
    {
        errorCode = listAppend(list, tempRecord);
    }

    free(tempRecord);
    fclose(file);
    return errorCode;
}

int main()
{
    List *list = NULL;
    int errorCode = createList(&list, sizeof(Record));
    if (errorCode == -1)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    char fileName[101] = {'\0'};
    printf("Enter file path (no longer than 100 symbols): ");
    scanf("%100s", fileName);

    int readCode = readDataFromFile(list, fileName);
    if (readCode == -3)
    {
        printf("File with this name doesn't exist!\n");
        return -3;
    }
    if (readCode == -4)
    {
        printf("Given file contains incorrect data!\n");
        return -4;
    }
    if (readCode == -1)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    signed char command = readCommand();
    while (command != 0)
    {
        switch (command)
        {
        case 1:
        {
            if (msort(list, compareByPhoneNumber))
            {
                printf("Succesfully sorted list by phone number");
            }
            else
            {
                printf("Unexpected error occured during sorting!");
            }
            break;
        }
        case 2:
        {
            if (msort(list, compareByName))
            {
                printf("Succesfully sorted list by name");
            }
            else
            {
                printf("Unexpected error occured during sorting!");
            }
            break;
        }
        case 3:
        {
            printf("Records:\n");
            listForEach(list, printRecord);
            break;
        }
        }
        command = readCommand();
    }

    listFree(list);
    free(list);
    return 0;
}