#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define strSize 16

// #define DEBUG 1

bool testString(size_t strLen, char *str)
{
    char *stack = malloc(strSize * sizeof(char));
    long long stackTop = -1;
    long long stackSize = strSize;

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
            if (stackTop % strSize == 0 && stackTop == stackSize)
            {
                stackSize += 16;
                stack = realloc(stack, (stackSize + strSize) * sizeof(char));
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
                free(stack);
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
                free(stack);
                return 0;
            }
            break;
        }
        case '\0':
        {
            free(stack);
            return 1;
        }
        };
    }
    free(stack);
    return stackTop == -1;
}

#if defined DEBUG
int test()
{
    int t = 0;
    if (!testString(4, "(())"))
    {
        printf("Test failed! String = \"(())\"\n");
        t = -1;
    }
    if (!testString(8, "({[()]})"))
    {
        printf("Test failed! String = \"({[()]})\"\n");
        t = -1;
    }
    if (testString(3, "(()"))
    {
        printf("Test failed! String = \"(()\"");
        t = -1;
    }
    if (!testString(34, "(afssdosidjif{1sadasd}fsdfs[123])\n"))
    {
        printf("Test failed! String = \"(afssdosidjif{1sadasd}fsdfs[123])\"\n");
        t = -1;
    }
    return t;
}
#endif

int main()
{
#if defined DEBUG
    printf("test result: %d\n", test());
#endif
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

    free(str);
}