#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// #define DEBUG 1

// Ingore warning for multi-line comments
#pragma GCC diagnostic ignored "-Wcomment"

// Finite-state machine.
// Regex: [A-Za-z]([A-Za-z]|[0-9]|_)*
// Diagram:
//
//      *other*   *other*
//    ----------> ------> 2 <---
//   /           /        |     |
//   |           |        \     /
//   |           |         -----
//   0 -------> (1) <-------------
//   [A-Za-z]    |                \             
//               \                /
//                ----------------
//                [A-Za-z]|[0-9]|_
//
// Table:
// | State | [A-Za-z] | [0-9] |  _  | other |
// |-------|----------|-------|-----|-------|
// |   0   |    1     |   2   |  2  |   2   |
// |   1   |    1     |   1   |  1  |   2   |
// |   2   |    2     |   2   |  2  |   2   |
// |-------|----------|-------|-----|-------|
//
// 0 - start state
// 1 - final state
// 2 - error state
int nextState(char curChar, int curState)
{
    switch (curState)
    {
    case 0:
        if (curChar >= 'A' && curChar <= 'Z')
        {
            curState = 1;
        }
        else if (curChar >= 'a' && curChar <= 'z')
        {
            curState = 1;
        }
        else
        {
            curState = 2;
        }
        break;
    case 1:
        if (curChar >= 'A' && curChar <= 'Z')
        {
            curState = 1;
        }
        else if (curChar >= 'a' && curChar <= 'z')
        {
            curState = 1;
        }
        else if (curChar >= '0' && curChar <= '9')
        {
            curState = 1;
        }
        else if (curChar == '_')
        {
            curState = 1;
        }
        else
        {
            curState = 2;
        }
        break;
    }
    return curState;
}

bool expressionMatch(char *str)
{
    int curState = 0;
    for (; *str != '\0'; ++str)
    {
        curState = nextState(*str, curState);
        if (curState == 2)
        {
            return false;
        }
    }
    return curState == 1;
}

#ifdef DEBUG
bool test1()
{
    char *str = "a";
    return expressionMatch(str);
}

bool test2()
{
    char *str = "a1_CD";
    return expressionMatch(str);
}

bool test3()
{
    char *str = "_a";
    return !expressionMatch(str);
}

bool test4()
{
    char *str = "a+1";
    return !expressionMatch(str);
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test 1 result: %s\n", test1() ? "OK" : "FAIL");
    printf("Test 2 result: %s\n", test2() ? "OK" : "FAIL");
    printf("Test 3 result: %s\n", test3() ? "OK" : "FAIL");
    printf("Test 4 result: %s\n", test4() ? "OK" : "FAIL");
#endif
    char *str = calloc(16, sizeof(char));
    size_t strSize = 16;
    if (str == NULL)
    {
        printf("Error allocating memory!\n");
        return -1;
    }
    printf("Enter string to check if it matches regex [A-Za-z]([A-Za-z]|[0-9]|_)*: ");
    while (true)
    {
        for (size_t i = strSize - 16; i < strSize; ++i)
        {
            str[i] = getc(stdin);
            if (str[i] == '\n')
            {
                str[i] = '\0';
                break;
            }
        }
        if (str[strSize - 1] != '\0')
        {
            str = realloc(str, strSize + 16);
            if (str == NULL)
            {
                printf("\nError allocating memory!\n");
                return -1;
            }
            for (size_t i = strSize; i < strSize + 16; ++i)
            {
                str[i] = '\0';
            }
            strSize += 16;
        }
        else
        {
            break;
        }
    }
    if (expressionMatch(str))
    {
        printf("String matches regex!\n");
    }
    else
    {
        printf("String doesn't match regex!\n");
    }

    free(str);
    return 0;
}