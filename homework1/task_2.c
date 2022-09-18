#include <stdio.h>
#include <stdbool.h>

#define ubyte unsigned char

// #define DEBUG 1

int div(int dividend, int divider)
{
    const bool isNegative = (dividend < 0) ^ (divider < 0);
    if (dividend < 0)
    {
        dividend = -dividend;
    }
    if (divider < 0)
    {
        divider = -divider;
    }

    int quotient = 0;
    
    for (int powerOfTwo = 1073741824; powerOfTwo != 0; powerOfTwo >>= 1)
    {
        if ((powerOfTwo + quotient) * (long long)divider <= dividend)
        {
            quotient += powerOfTwo;
        }
    }

    if (isNegative)
    {
        return -quotient;
    }
    return quotient;
}

#if defined DEBUG
int test()
{
    for (int dividend = -10; dividend <= 10; dividend++)
    {
        for (int divider = -10; divider <= 10; divider++)
        {
            if (divider == 0)
            {
                divider++;
            }
            int quotient = div(dividend, divider);
            if (quotient != dividend / divider)
            {
                printf("Test failed: x = %d, y = %d, x / y = %d, div(x, y) = %d\n", dividend, divider, dividend / divider, quotient);
                return -1;
            }
        }
    }
    return 0;
}
#endif

int main()
{
#if defined DEBUG
    printf("test result: %d\n", test());
#endif
    int dividend, divider;
    printf("Enter dividend: ");
    scanf("%d", &dividend);
    printf("Enter divider: ");
    scanf("%d", &divider);
    if (divider == 0)
    {
        printf("Cannot divide by zero!");
        return 3221225620;
    }
    printf("quotient = %d\n", div(dividend, divider));
}