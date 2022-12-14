#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define uint unsigned int

uint recursiveFibbonaci(uint n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n <= 2)
    {
        return 1;
    }

    return recursiveFibbonaci(n - 1) + recursiveFibbonaci(n - 2);
}

uint iterativeFibbonaci(uint n)
{
    uint latestNumber = 0, preLatestNumber = 1;

    for (uint i = 0; i < n; ++i)
    {
        latestNumber = latestNumber + preLatestNumber;
        preLatestNumber = latestNumber - preLatestNumber;
    }

    return latestNumber;
}

int main()
{
    while (1)
    {
        uint n = 0;

        printf("Enter positive number N to get Nth fibonacci number (or enter 0 to exit program): ");
        int scanResult = scanf("%u", &n);
        while (scanResult == 0)
        {
            scanf("%*[^\n]");
            printf("Wrong input! Please enter positive number: ");
            scanResult = scanf("%u", &n);
        }

        if (n == 0)
        {
            break;
        }

        const clock_t clockAtStartIterative = clock();
        const uint answerIterative = iterativeFibbonaci(n);
        const clock_t clockAtEndIterative = clock();

        printf("Iterative method took %.3f seconds! Answer is %u\n", (float)(clockAtEndIterative - clockAtStartIterative) / CLOCKS_PER_SEC, answerIterative);

        const clock_t clockAtStartRecursive = clock();
        const uint answerRecursive = recursiveFibbonaci(n);
        const clock_t clockAtEndRecursive = clock();

        printf("Recursive method took %.3f seconds! Answer is %u\n", (float)(clockAtEndRecursive - clockAtStartRecursive) / CLOCKS_PER_SEC, answerRecursive);
    }
    return 0;
}