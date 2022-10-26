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

        const clock_t clockAtStartIt = clock();
        const uint ansIt = iterativeFibbonaci(n);
        const clock_t clockAtEndIt = clock();

        printf("Iterative method took %.3f seconds! Answer is %u\n", (float)(clockAtEndIt - clockAtStartIt) / CLOCKS_PER_SEC, ansIt);

        const clock_t clockAtStartRe = clock();
        const uint ansRe = recursiveFibbonaci(n);
        const clock_t clockAtEndRe = clock();

        printf("Recursive method took %.3f seconds! Answer is %u\n", (float)(clockAtEndRe - clockAtStartRe) / CLOCKS_PER_SEC, ansRe);
    }
    return 0;
}