#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RECORDS 100

typedef struct Record
{
    char phoneNumber[16];
    char name[51];
} Record;

signed char readCommand()
{
    printf("Input command (0 - exit, 1 - add record to database, 2 - print all records in database, 3 - find phone by name, 4 - find name by phone, 5 - save database to file): ");
    signed char command = -1;
    int scanResult = scanf("%hhi", &command);
    while (scanResult == 0 || command > 5 || command < 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please try again: ");
        scanResult = scanf("%hhi", &command);
    }
    return command;
}

void executeCommand1(Record **records, size_t *lastRecord)
{
    if (*lastRecord >= MAX_RECORDS)
    {
        printf("Database is full, cannot add new record!\n");
        return;
    }
    printf("Enter phone number (no longer than 15 symbols, without spaces): ");
    scanf("%s", records[*lastRecord]->phoneNumber);
    printf("Enter name (no longer than 50 symbols, without spaces): ");
    scanf("%s", records[*lastRecord]->name);
    ++*lastRecord;
}

void executeCommand2(Record **records, size_t lastRecord)
{
    for (size_t i = 0; i < lastRecord; ++i)
    {
        printf("Phone number: %s, Name: %s\n", records[i]->phoneNumber, records[i]->name);
    }
}

void executeCommand3(Record **records, size_t lastRecord)
{
    printf("Enter name to find (no longer than 50 symbols): ");
    char name[51] = {0};
    scanf("%s", name);

    bool found = false;

    for (size_t i = 0; i < lastRecord; ++i)
    {
        if (strcmp(name, records[i]->name) == 0)
        {
            printf("Found phone number by given name: %s\n", records[i]->phoneNumber);
            found = true;
        }
    }

    if (!found)
    {
        printf("No record with this name in database!\n");
    }
}

void executeCommand4(Record **records, size_t lastRecord)
{

    printf("Enter phone number to find (no longer than 15 symbols, without spaces): ");
    char phoneNumber[16] = {0};
    scanf("%s", phoneNumber);

    bool found = false;

    for (size_t i = 0; i < lastRecord; ++i)
    {
        if (strcmp(phoneNumber, records[i]->phoneNumber) == 0)
        {
            printf("Found name by given phone number: %s\n", records[i]->name);
            found = true;
        }
    }

    if (!found)
    {
        printf("No record with this phone number in database!\n");
    }
}

int executeCommand5(Record **records, size_t lastRecord, char **fileName)
{
    char tmp[101] = {0};
    printf("Enter file name (or enter \"0\" to save data to previous file): ");
    scanf("%s", tmp);
    while (tmp[100] != 0)
    {
        printf("Wrong input! Enter no more than 100 symbols: ");
        for (size_t i = 0; i < 101; ++i)
        {
            tmp[i] = 0;
        }
        scanf("%s", tmp);
    }

    if (strcmp(tmp, "0"))
    {
        strcpy(tmp, *fileName);
    }

    FILE *file = fopen(*fileName, "w");
    if (file == NULL)
    {
        return -3;
    }

    fprintf(file, "phoneNumber\tname");
    for (size_t i = 0; i < lastRecord; ++i)
    {
        fprintf(file, "\n%s\t%s", records[i]->phoneNumber, records[i]->name);
    }
    fclose(file);
    return 0;
}

int readDataFromFile(Record **records, char *fileName, size_t *lastRecord)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -3;
    }
    char tmp[17] = {0};
    char heading[] = "phoneNumber\tname";

    fscanf(file, "%s", tmp);
    tmp[11] = '\t';
    fscanf(file, "%s", tmp + 12);

    if (strcmp(heading, tmp))
    {
        fclose(file);
        return -4;
    }

    while (!feof(file))
    {
        fscanf(file, "%s %s", records[*lastRecord]->phoneNumber, records[*lastRecord]->name);
        ++*lastRecord;
    }

    fclose(file);
    return 0;
}

void freeRecords(Record **records)
{
    for (size_t i = 0; i < MAX_RECORDS; ++i)
    {
        free(records[i]);
    }
}

int main()
{
    char *fileName = calloc(101, sizeof(char));

    Record *records[MAX_RECORDS] = {NULL};
    for (size_t i = 0; i < MAX_RECORDS; ++i)
    {
        records[i] = calloc(1, sizeof(Record));
        if (records[i] == NULL)
        {
            printf("Error allocating memory!");
            freeRecords(records);
            return -2;
        }
    }
    size_t lastRecord = 0;

    printf("Enter file path (no longer than 100 symbols) or enter \"0\" to work with new database: ");
    scanf("%s", fileName);
    while (fileName[100] != 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Enter no more than 100 symbols: ");
        for (size_t i = 0; i < 101; ++i)
        {
            fileName[i] = 0;
        }
        scanf("%s", fileName);
    }

    if (strcmp(fileName, "0"))
    {
        int readCode = readDataFromFile(records, fileName, &lastRecord);
        if (readCode == -3)
        {
            printf("File with this name doesn't exist! Working with new database instead\n");
        }
        else if (readCode == -4)
        {
            printf("Given file contains incorrect data! Working with new database instead\n");
        }
    }

    signed char command = readCommand();
    while (command != 0)
    {
        switch (command)
        {
        case 1:
            executeCommand1(records, &lastRecord);
            break;
        case 2:
            executeCommand2(records, lastRecord);
            break;
        case 3:
            executeCommand3(records, lastRecord);
            break;
        case 4:
            executeCommand4(records, lastRecord);
            break;
        case 5:
        {
            int result = executeCommand5(records, lastRecord, &fileName);
            if (result == -3)
            {
                printf("File with this name doesn't exist!\n");
            }
            else if (result == 0)
            {
                printf("Saved database to file!\n");
            }
            break;
        }
        }
        command = readCommand();
    }

    free(fileName);
    return 0;
}