#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.h"

int add(int a, int b) { return a + b; }
int substract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int makeArithmeticOperation(Stack *stack, int (*operation)(int, int))
{
    int firstOperand = 0, secondOperand = 0;

    int errorCode = stackPop(stack, &firstOperand);
    if (errorCode == -3)
    {
        return -3;
    }
    errorCode = stackPop(stack, &secondOperand);
    if (errorCode == -3)
    {
        return -3;
    }

    if (operation == divide && firstOperand == 0)
    {
        return -4;
    }
    firstOperand = operation(secondOperand, firstOperand);
    errorCode = stackPush(stack, &firstOperand);
    if (errorCode == -1)
    {
        return -1;
    }

    return 0;
}

int main()
{
    Stack *stack = NULL;
    int errorCode = createStack(&stack, sizeof(int));
    if (errorCode == -1)
    {
        printf("Error allocating memory!\n");
        return -1;
    }

    printf("Input arithmetic equation in postfix form (every number must contain only 1 digit): ");

    for (char c = getc(stdin); c != '\n'; c = getc(stdin))
    {
        switch (c)
        {
        case ' ':
        case '\t':
            break;
        case '+':
        {
            int errorCode = makeArithmeticOperation(stack, add);
            if (errorCode == -3)
            {
                printf("Incorrect input!\n");
                free(stack);
                return 1;
            }
            if (errorCode == -1)
            {
                printf("Error allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case '-':
        {
            int errorCode = makeArithmeticOperation(stack, substract);
            if (errorCode == -3)
            {
                printf("Incorrect input!\n");
                free(stack);
                return 1;
            }
            if (errorCode == -1)
            {
                printf("Error allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case '*':
        {
            int errorCode = makeArithmeticOperation(stack, multiply);
            if (errorCode == -3)
            {
                printf("Incorrect input!\n");
                free(stack);
                return 1;
            }
            if (errorCode == -1)
            {
                printf("Error allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        case '/':
        {
            int errorCode = makeArithmeticOperation(stack, divide);
            if (errorCode == -3)
            {
                printf("Incorrect input!\n");
                free(stack);
                return 1;
            }
            if (errorCode == -4) {
                printf("Cannot divide by zero!\n");
                stackFree(stack);
                free(stack);
                return 2;
            }
            if (errorCode == -1)
            {
                printf("Error allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
            break;
        }
        default:
        {
            int num = c - '0';
            if (num > 9 || num < 0)
            {
                printf("Incorrect input!\n");
                stackFree(stack);
                free(stack);
                return 1;
            }
            int errorCode = stackPush(stack, &num);
            if (errorCode == -1)
            {
                printf("Error allocating memory!\n");
                stackFree(stack);
                free(stack);
                return -1;
            }
        }
        }
    }

    int result = 0;
    errorCode = stackPop(stack, &result);
    if (errorCode == -3)
    {
        printf("Incorrect input!\n");
        free(stack);
        return 1;
    }
    if (!stackEmptyOrNULL(stack))
    {
        printf("Incorrect input!\n");
        stackFree(stack);
        free(stack);
        return 1;
    }

    printf("Result: %d\n", result);
    free(stack);
    return 0;
}