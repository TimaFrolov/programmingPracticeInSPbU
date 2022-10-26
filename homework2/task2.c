#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

#define powType float

// #define DEBUG 1

powType slowPower(powType base, uint power)
{
    powType ans = 1;
    for (uint i = 0; i < power; ++i)
    {
        ans *= base;
    }
    return ans;
}

powType fastPower(powType base, uint power)
{
    uint powerOfTwo = 1;

    powType powerOfBase = base;
    powType ans = 1;

    while (powerOfTwo <= power)
    {
        if (powerOfTwo & power)
        {
            ans *= powerOfBase;
        }
        powerOfBase *= powerOfBase;
        powerOfTwo <<= 1;
    }

    return ans;
}

#ifdef DEBUG
int test(void)
{
    int testResult = 0;

    for (powType base = 1; base < 10; base += 1)
    {
        for (uint power = 1; power < 10; ++power)
        {
            if (fastPower(base, power) != slowPower(base, power))
            {
                printf("Test falied! base = %f, power = %d, fastPower = %f, slowPower = %f\n", base, power, fastPower(base, power), slowPower(base, power));
                testResult = -1;
            }
        }
    }

    return testResult;
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test result = %d\n", test());
#endif
    powType base = 1;
    uint power = 1;

    printf("Enter exponent base (floating point number):");
    int scanResult = scanf("%f", &base);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter floating point number: ");
        scanResult = scanf("%f", &base);
    }

    printf("Enter exponent power (natural number): ");
    scanResult = scanf("%u", &power);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%u", &power);
    }

    printf("%.3f to the power of %d = %.3f\n", base, power, fastPower(base, power));
    return 0;
}