#include <stdio.h>
#include <stdbool.h>

int main()
{
    char fileName[101] = {0};
    printf("Enter file path (no longer than 100 symbols): ");
    int scanResult = scanf("%s", fileName);
    while (scanResult == 0 || fileName[100] != 0)
    {
        printf("Wrong input! Enter no more than 100 symbols: ");
        for (size_t i = 0; i < 101; ++i)
        {
            fileName[i] = 0;
        }
        scanResult = scanf("%s", fileName);
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("File with this name doesn't exist!\n");
        return -1;
    }

    printf("Comments in file:\n");

    bool isComment = 0;
    while (!feof(file))
    {
        const char character = fgetc(file);
        if (feof(file))
        {
            break;
        }
        if (character == ';')
        {
            isComment = 1;
        }
        if (isComment)
        {
            printf("%c", character);
        }
        if (character == '\n')
        {
            isComment = 0;
        }
    }
    fclose(file);
    printf("\n");
    printf("No more comments in file!\n");
}