#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define strSize 16

bool testString(size_t strLen, char *str)
{
    char *stack = malloc(strSize * sizeof(char));
    long long stackTop = -1;

    for (size_t i = 0; i < strLen; ++i)
    {
        switch (str[i])
        {
        case '(':
        case '{':
        case '[':
        case '<':
        {
            ++stackTop;
            if (stackTop && stackTop % strSize == 0)
            {
                stack = realloc(stack, (i + strSize) * sizeof(char));
            }
            stack[stackTop] = str[i];
            break;
        }
        case ')':
        {
            if (stackTop >= 0 && stack[stackTop] == '(')
            {
                stack[stackTop] = '\0';
                --stackTop;
            }
            else
            {
                return 0;
            }
            break;
        }
        case '}':
        case ']':
        case '>':
        {
            if (stackTop >= 0 && stack[stackTop] == str[i] - 2) // index for closing brackets for
            {                                                   // '<','{','[' in ascii table is equal
                stack[stackTop] = '\0';                         // to number of opening bracket + 2,
                --stackTop;                                     // while for '(' it is only '+1'.
            }
            else
            {
                return 0;
            }
            break;
        }
        case '\0':
            return 1;
        };
    }

    if (stackTop == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char *str = malloc(strSize * sizeof(char));
    printf("Enter a string to check proper use of brackets: ");
    size_t strLen = 0;
    do
    {
        if (strLen && strLen % strSize == 0)
        {
            str = realloc(str, (strLen + strSize) * sizeof(char));
        }
        str[strLen] = getc(stdin);
        ++strLen;
    } while (str[strLen - 1] != '\n');
    str[strLen] = '\0';

    if (testString(strLen, str))
    {
        printf("Brackets are used properly!\n");
    }
    else
    {
        printf("Brackets aren't used properly :(\n");
    }
}