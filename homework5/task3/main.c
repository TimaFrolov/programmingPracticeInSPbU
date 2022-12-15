#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

int main()
{
    Stack *stack = NULL;
    int errorCode = createStack(&stack, sizeof(char));
    if (errorCode == -1)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    printf("Input arithmetic equation in infix form (every number must contain only 1 digit) so programm will print it in postfix form: ");

    for (char curChar = getc(stdin); curChar != '\n'; curChar = getc(stdin))
    {
        switch (curChar)
        {
        case ' ':
            break;
        case '+':
        case '-':
        {
            char topValue = '\0';
            int errorCode = stackPop(stack, &topValue);
            while (errorCode == 0 && (topValue == '+' || topValue == '-' || topValue == '*' || topValue == '/'))
            {
                printf(" %c", topValue);
                errorCode = stackPop(stack, &topValue);
            }
            if (errorCode == 0)
            {
                errorCode = stackPush(stack, &topValue);
                if (errorCode == -1)
                {
                    printf("\nError allocating memory!\n");
                    stackFree(stack);
                    free(stack);
                    return -1;
                }
            }
            errorCode = stackPush(stack, &curChar);
            if (errorCode == -1)
            {
                printf("\nError allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case '*':
        case '/':
        {
            char topValue = '\0';
            int errorCode = stackPop(stack, &topValue);
            while (errorCode == 0 && (topValue == '*' || topValue == '/'))
            {
                printf("%c", topValue);
                errorCode = stackPop(stack, &topValue);
            }
            if (errorCode == 0)
            {
                errorCode = stackPush(stack, &topValue);
                if (errorCode == -1)
                {
                    printf("\nError allocating memory!\n");
                    stackFree(stack);
                    free(stack);
                    return -1;
                }
            }
            errorCode = stackPush(stack, &curChar);
            if (errorCode == -1)
            {
                printf("\nError allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case '(':
        {
            errorCode = stackPush(stack, &curChar);
            if (errorCode == -1)
            {
                printf("\nError allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case ')':
        {
            char topValue = '\0';
            int errorCode = stackPop(stack, &topValue);
            while (errorCode == 0 && topValue != '(')
            {
                printf(" %c", topValue);
                errorCode = stackPop(stack, &topValue);
            }
            if (errorCode == -3)
            {
                printf("\nIncorrect input!\n");
                stackFree(stack);
                free(stack);
                return 1;
            }
            break;
        }
        default:
        {
            int num = curChar - '0';
            if (num > 9 || num < 0)
            {
                printf("\nIncorrect input!\n");
                stackFree(stack);
                free(stack);
                return 1;
            }
            printf(" %d", num);
        }
        }
    }
    char topValue = '\0';
    errorCode = stackPop(stack, &topValue);
    while (errorCode == 0)
    {
        printf(" %c", topValue);
        errorCode = stackPop(stack, &topValue);
    }
    printf("\n");

    return 0;
}