#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../stack/stack.h"

// #define DEBUG 1

// Error codes: -1 = error allocating memory, 0 = OK
int testString(char *str, bool *result)
{
    Stack *stack = NULL;
    int errorCode = createStack(&stack, sizeof(char));
    if (errorCode == -1)
    {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
        case '(':
        case '{':
        case '[':
        case '<':
        {
            int errorCode = stackPush(stack, &str[i]);
            if (errorCode == -1)
            {
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case ')':
        {
            char topValue = '\0';
            stackPop(stack, &topValue);

            if (topValue != '(')
            {
                stackFree(stack);
                free(stack);
                *result = false;
                return 0;
            }
            break;
        }
        case '}':
        case ']':
        case '>':
        {
            char topValue = '\0';
            stackPop(stack, &topValue);

            if (topValue != str[i] - 2) // difference in numbers between closing and opening
            {                           // brackets for '<>','{}','[]' in ascii table is equal to 2,
                stackFree(stack);       // while for '()' it is only 1
                free(stack);
                *result = false;
                return 0;
            }
            break;
        }
        };
    }
    *result = stackEmptyOrNULL(stack);
    stackFree(stack);
    free(stack);
    return 0;
}

#ifdef DEBUG
bool test1()
{
    bool result = false;
    int errorCode = testString("(())", &result);
    if (errorCode != 0 || !result)
    {
        printf("Test failed! Error code = %d, string = \"(())\", result = %d\n", errorCode, result);
    }
    return errorCode == 0 && result;
}
bool test2()
{
    bool result = false;
    int errorCode = testString("({[()]})", &result);
    if (errorCode != 0 || !result)
    {
        printf("Test failed! Error code = %d, string = \"({[()]})\", result = %d\n", errorCode, result);
    }
    return errorCode == 0 && result;
}
bool test3()
{
    bool result = false;
    int errorCode = testString("(()", &result);
    if (errorCode != 0 || result)
    {
        printf("Test failed! Error code = %d, string = \"(()\", result = %d\n", errorCode, result);
    }
    return errorCode == 0 && !result;
}
bool test4()
{
    bool result = false;
    int errorCode = testString("(afssdosidjif{1sadasd}fsdfs[123])", &result);
    if (errorCode != 0 || !result)
    {
        printf("Test failed! Error code = %d, string = \"(afssdosidjif{1sadasd}fsdfs[123])\", result = %d\n", errorCode, result);
    }
    return errorCode == 0 && result;
}
#endif

int main()
{
#if defined DEBUG
    printf("Test 1 result: %d\n", test1());
    printf("Test 2 result: %d\n", test2());
    printf("Test 3 result: %d\n", test3());
    printf("Test 4 result: %d\n", test4());
#endif

    size_t strLen = 0;
    printf("Enter length of string (natural number): ");
    int scanResult = scanf("%lu", &strLen);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%lu", &strLen);
    }

    char *str = calloc(strLen + 1, sizeof(char));
    if (str == NULL)
    {
        printf("Error allocating memory!\n");
        return -1;
    }
    printf("Enter a string to check proper use of brackets: ");

    scanf("%s", str);
    if (str[strLen] != '\0')
    {
        printf("Given string is longer than %lu symbols! Cannot continue executing program\n", strLen);
        free(str);
        return 1;
    }

    bool testResult = false;

    int errorCode = testString(str, &testResult);

    free(str);

    if (errorCode == -1)
    {
        printf("Error allocating memory!\n");
        return 0;
    }

    if (testResult)
    {
        printf("Brackets are used properly!\n");
    }
    else
    {
        printf("Brackets aren't used properly :(\n");
    }

    return 0;
}