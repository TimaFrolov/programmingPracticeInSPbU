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

int executeCommand1(Record **records, size_t *countRecords)
{
    if (*countRecords >= MAX_RECORDS)
    {
        printf("Database is full, cannot add new record!\n");
        return 0;
    }

    records[*countRecords] = calloc(1, sizeof(Record));
    if (records[*countRecords] == NULL)
    {
        return -2;
    }

    printf("Enter phone number (no longer than 15 symbols, without spaces): ");
    scanf("%15s", records[*countRecords]->phoneNumber);
    printf("Enter name (no longer than 50 symbols, without spaces): ");
    scanf("%50s", records[*countRecords]->name);
    ++*countRecords;

    return 0;
}

void executeCommand2(Record **records, size_t countRecords)
{
    for (size_t i = 0; i < countRecords; ++i)
    {
        printf("Phone number: %s, Name: %s\n", records[i]->phoneNumber, records[i]->name);
    }
}

void executeCommand3(Record **records, size_t countRecords)
{
    printf("Enter name to find (no longer than 50 symbols): ");
    char name[51] = {0};
    scanf("%50s", name);

    bool found = false;

    for (size_t i = 0; i < countRecords; ++i)
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

void executeCommand4(Record **records, size_t countRecords)
{

    printf("Enter phone number to find (no longer than 15 symbols, without spaces): ");
    char phoneNumber[16] = {0};
    scanf("%15s", phoneNumber);

    bool found = false;

    for (size_t i = 0; i < countRecords; ++i)
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

int executeCommand5(Record **records, size_t countRecords, char **fileName)
{
    char tmp[101] = {0};
    printf("Enter file name (or enter \"0\" to save data to previous file): ");
    scanf("%100s", tmp);

    if (strcmp(tmp, "0"))
    {
        strcpy(*fileName, tmp);
    }

    FILE *file = fopen(*fileName, "w");
    if (file == NULL)
    {
        return -3;
    }

    fprintf(file, "phoneNumber\tname");
    for (size_t i = 0; i < countRecords; ++i)
    {
        fprintf(file, "\n%s\t%s", records[i]->phoneNumber, records[i]->name);
    }
    fclose(file);
    return 0;
}

int readDataFromFile(Record **records, char *fileName, size_t *countRecords)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        return -3;
    }
    char tmp[17] = {0};
    char heading[] = "phoneNumber\tname";

    fscanf(file, "%11s", tmp);
    tmp[11] = '\t';
    fscanf(file, "%4s", tmp + 12);

    if (strcmp(heading, tmp))
    {
        fclose(file);
        return -4;
    }

    while (!feof(file))
    {
        records[*countRecords] = calloc(1, sizeof(Record));
        if (records[*countRecords] == NULL)
        {
            fclose(file);
            return -2;
        }
        fscanf(file, "%s %s", records[*countRecords]->phoneNumber, records[*countRecords]->name);
        ++*countRecords;
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
    size_t countRecords = 0;

    printf("Enter file path (no longer than 100 symbols) or enter \"0\" to work with new database: ");
    scanf("%100s", fileName);

    if (strcmp(fileName, "0"))
    {
        int readCode = readDataFromFile(records, fileName, &countRecords);
        switch (readCode)
        {
        case -2:
        {
            printf("Error allocating memory!");
            freeRecords(records);
            return -2;
        }
        case -3:
        {
            printf("File with this name doesn't exist! Working with new database instead\n");
            break;
        }
        case -4:
        {
            printf("Given file contains incorrect data! Working with new database instead\n");
            break;
        }
        }
    }

    signed char command = readCommand();
    while (command != 0)
    {
        switch (command)
        {
        case 1:
        {
            int result = executeCommand1(records, &countRecords);
            if (result == -2)
            {
                printf("Error allocating memory!");
                freeRecords(records);
                return -2;
            }
            break;
        }
        case 2:
            executeCommand2(records, countRecords);
            break;
        case 3:
            executeCommand3(records, countRecords);
            break;
        case 4:
            executeCommand4(records, countRecords);
            break;
        case 5:
        {
            int result = executeCommand5(records, countRecords, &fileName);
            if (result == -3)
            {
                printf("Cannot write to file with this path\n");
            }
            else
            {
                printf("Saved database to file!\n");
            }
            break;
        }
        }
        command = readCommand();
    }

    free(fileName);
    freeRecords(records);
    return 0;
}