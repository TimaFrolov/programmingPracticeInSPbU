#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <stdlib.h>

typedef enum
{
    INCORRECT,
    EXIT,
    PUSH,
    POP,
    ADD,
    PRINT
} Command;

Command getCommand()
{
    char buffer[10] = {0};
    scanf("%s", buffer);
    if (buffer[5] != 0)
    {
        return INCORRECT;
    }
    if (strcmp(buffer, "exit") == 0)
    {
        return EXIT;
    }
    if (strcmp(buffer, "push") == 0)
    {
        return PUSH;
    }
    if (strcmp(buffer, "pop") == 0)
    {
        return POP;
    }
    if (strcmp(buffer, "add") == 0)
    {
        return ADD;
    }
    if (strcmp(buffer, "print") == 0)
    {
        return PRINT;
    }
    return INCORRECT;
}

int main()
{
    Stack *stack = NULL;
    Error creationError = createStack(&stack);
    if (creationError == MemoryAllocationError)
    {
        printf("Memory allocation error!\n");
        return -1;
    }
    while (1)
    {
        printf("Enter command (list of commands: 'exit', 'push <number>', 'pop', 'add', 'print'): ");
        switch (getCommand())
        {
        case EXIT:
        {
            stackFree(stack);
            free(stack);
            return 0;
        }
        case PUSH:
        {
            int num = 0;
            int scanResult = scanf("%d", &num);
            if (scanResult == 0)
            {
                scanf("%*[^\n]");
                printf("Incorrect command usage!\n");
                break;
            }
            Error pushError = stackPush(stack, num);
            if (pushError == MemoryAllocationError)
            {
                printf("Memory allocation error!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            printf("Succesfully pushed value into stack\n");
            break;
        }
        case POP:
        {
            int num = 0;
            Error popError = stackPop(stack, &num);
            if (popError == StackIsEmpty)
            {
                printf("Cannot pop number from stack because it is empty\n");
                break;
            }
            printf("Succesfully popped number from stack. It was %d\n", num);
            break;
        }
        case ADD:
        {
            int num1 = 0;
            int num2 = 0;
            Error popError1 = stackPop(stack, &num1);
            Error popError2 = stackPop(stack, &num2);
            if (popError2 == StackIsEmpty)
            {
                printf("Cannot execute given command: not enough numbers in stack\n");
                if (popError1 != StackIsEmpty)
                {
                    Error pushError = stackPush(stack, num1);
                    if (pushError == MemoryAllocationError)
                    {
                        printf("Memory allocation error!\n");
                        stackFree(stack);
                        free(stack);
                        return -1;
                    }
                }
                break;
            }
            stackPush(stack, num1 + num2);
            printf("Succesfully executed command\n");
            break;
        }
        case PRINT:
        {
            printf("All number in stack (from top to bottom): ");
            stackPrint(stack);
            printf("\n");
            break;
        }
        case INCORRECT:
        {
            scanf("%*[^\n]");
            printf("Incorrect command!\n");
            break;
        }
        }
    }
}