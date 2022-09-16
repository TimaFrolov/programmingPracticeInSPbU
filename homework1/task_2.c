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

    const int powersOfTwo[] = {1073741824, 536870912, 268435456, 134217728, 67108864, 33554432,
                               16777216, 8388608, 4194304, 2097152, 1048576, 524288, 262144, 131072,
                               65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32,
                               16, 8, 4, 2, 1};

    // Could have used bit shift instead of this array, but task says "only addition, multiplication and subtraction"

    int quotient = 0;
    for (ubyte i = 0; i < 31; ++i)
    {
        if ((powersOfTwo[i] + quotient) * (long long)divider <= dividend)
        {
            quotient += powersOfTwo[i];
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