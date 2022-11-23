#include <stdio.h>

int getNextDate(FILE *file)
{
    while (!feof(file))
    {
        short curChar = fgetc(file);
        if (curChar == -1)
        {
            return -1;
        }
        if (curChar < '0' || curChar > '9')
        {
            continue;
        }
        ungetc(curChar, file);
        int day = 0;
        int month = 0;
        int year = 0;
        int scanResult = -1;
        fscanf(file, "%d", &day);
        if (getc(file) != '.' || day > 31 || day < 1)
        {
            continue;
        }
        scanResult = fscanf(file, "%d", &month);
        if (scanResult == 0 || getc(file) != '.' || month > 12 || month < 1)
        {
            continue;
        }
        scanResult = fscanf(file, "%d", &year);
        if (scanResult == 0 || year < 1)
        {
            continue;
        }
        return day + month * 100 + year * 10000;
    }
    return -1;
}

int main()
{
    char filename[101] = {0};
    printf("Enter file path (no longer than 100 symbols): ");
    scanf("%s", filename);
    if (filename[100] != 0)
    {
        printf("Incorrect input!\n");
        return -1;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        return -2;
    }

    int maxDate = -1;

    while (!feof(file))
    {
        int curDate = getNextDate(file);
        if (curDate > maxDate)
        {
            maxDate = curDate;
        }
    }

    printf("Max date found in given file: ");

    int day = maxDate % 100;
    maxDate /= 100;
    int month = maxDate % 100;
    maxDate /= 100;
    int year = maxDate;
    if (day < 10)
    {
        printf("0");
    }
    printf("%d.", day);
    if (month < 10)
    {
        printf("0");
    }
    printf("%d.%d", month, year);

}