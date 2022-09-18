#include <stdio.h>

#define ushort unsigned short
#define ubyte unsigned char
#define byte signed char

#define maxSum 28

ushort countTickets()
{
    ushort sumCounts[maxSum] = {0};

    sumCounts[0] = 1;
    // to calculate amount of numbers with N digits with given sum of digits S we have to calculate
    // amount of numbers with N-1 digits with sum equal to S-digit for each digit from 0 to 9
    // (digit iterating in reverse order so changes in array doesn't affect future calculations in
    // this iteration; iterating to 1 but not to 0 because sumCounts[sum] already contains amount of
    // numbers for digit 0)
    // starting from amount of numbers = 0, so have to do N iterations
    for (ubyte iterations = 0; iterations < 3; ++iterations)
    {
        for (byte sum = maxSum - 1; sum >= 0; --sum)
        {
            for (byte digit = 9; digit > 0; --digit)
            {
                if (sum + digit < maxSum)
                {
                    sumCounts[sum + digit] += sumCounts[sum];
                }
            }
        }
    }

    ushort ans = 0;
    for (ubyte i = 0; i < maxSum; ++i)
    {
        ans += sumCounts[i] * sumCounts[i];
    }
    return ans;
}

int main()
{
    printf("Number of favourite tickets with 6 digits: %u\n", countTickets());
}