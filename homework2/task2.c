#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define powType float

// #define DEBUG 1

float absolute(float x)
{
    return x >= 0 ? x : -x;
}

powType slowPower(powType base, int power)
{
    if (power < 0)
    {
        base = 1 / base;
        power = -power;
    }
    powType ans = 1;
    for (int i = 0; i < power; ++i)
    {
        ans *= base;
    }
    return ans;
}

powType fastPower(powType base, int power)
{
    if (power < 0)
    {
        base = 1 / base;
        power = -power;
    }
    int powerOfTwo = 1;

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
bool test()
{
    bool testResult = true;

    for (powType base = 1; base < 10; base += 1)
    {
        for (int power = -10; power < 10; ++power)
        {
            if (absolute(fastPower(base, power) - slowPower(base, power)) > 1e-5)
            {
                printf("Test falied! base = %f, power = %d, fastPower = %f, slowPower = %f\n", base, power, fastPower(base, power), slowPower(base, power));
                testResult = false;
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
    int power = 1;

    printf("Enter exponent base (floating point number):");
    int scanResult = scanf("%f", &base);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter floating point number: ");
        scanResult = scanf("%f", &base);
    }

    printf("Enter exponent power (natural number): ");
    scanResult = scanf("%d", &power);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%d", &power);
    }

    printf("%.3f to the power of %d = %.3f\n", base, power, fastPower(base, power));
    return 0;
}