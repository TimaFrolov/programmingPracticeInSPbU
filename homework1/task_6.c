#include <stdio.h>
#include <stdlib.h>

void swap(char *a, char *b)
{
    const char tmp = *b;
    *b = *a;
    *a = tmp;
}

void reverse(size_t len, char *arr)
{
    for (size_t i = 0; i < len / 2; ++i)
    {
        swap(&arr[i], &arr[len - i - 1]);
    }
}

size_t count(size_t sLen, size_t s1Len, char *str)
{
    // Solution using z functions. If not familiar with them, check https://codeforces.com/edu/course/2/lesson/3
    size_t *zFunc = malloc((sLen + 2) * sizeof(size_t));
    zFunc[0] = 0;

    size_t firstCharIndex = 0, lastCharIndex = 0; // first and last char indexes of substring that
    size_t counter = 0;                           // is equal to prefix of string with length =
    for (size_t i = 1; i <= sLen + 1; ++i)        // = lastCharIndex - firstCharIndex
    {
        if (i <= lastCharIndex)
        {
            if (zFunc[i - firstCharIndex] < lastCharIndex - i + 1)
            {
                zFunc[i] = zFunc[i - firstCharIndex];
            }
            else
            {
                zFunc[i] = lastCharIndex - i + 1;
                while (str[i + zFunc[i]] == str[zFunc[i]])
                {
                    ++zFunc[i];
                }
            }
        }
        else
        {
            zFunc[i] = 0;
            while (str[i + zFunc[i]] == str[zFunc[i]])
            {
                ++zFunc[i];
            }
        }

        if (zFunc[i] == s1Len)
        {
            ++counter;
        }

        if (lastCharIndex < i + zFunc[i] - 1)
        {
            firstCharIndex = i;
            lastCharIndex = i + zFunc[i] - 1;
        }
    }

    return counter;
}

int main()
{
    size_t sLen;
    printf("Enter length of S: ");
    scanf("%llu", &sLen);

    char *str = malloc(sLen * sizeof(char));
    printf("Enter S: ");
    scanf("%s", str);

    size_t s1Len;
    printf("Enter length of S1: ");
    scanf("%llu", &s1Len);

    str = realloc(str, (s1Len + sLen + 1) * sizeof(char));
    printf("Enter S1: ");
    scanf("%s", str + sLen + 1);

    str[sLen] = '\036'; // record separator symbol, hope s and s1 doesn't contain it

    reverse(s1Len + sLen + 1, str);
    reverse(s1Len, str);
    reverse(sLen, str + s1Len + 1);

    printf("Number of occurances s1 in s: %llu\n", count(sLen, s1Len, str));
}