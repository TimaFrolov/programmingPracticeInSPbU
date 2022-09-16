#include <stdio.h>
#include <stdlib.h>

// #define DEBUG 1

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

    free(zFunc);

    return counter;
}

#if defined DEBUG
int test()
{
    size_t c;
    int t = 0;
    c = count(2, 1, "a\naa");
    if (c != 2)
    {
        printf("Test failed! str = \"aa\", substr=\"a\", expected 2, got %llu\n", c);
        t = -1;
    }
    c = count(10, 3, "aba\nabacababde");
    if (c != 2)
    {
        printf("Test failed! str = \"abacababde\", substr=\"aba\", expected 2, got %llu\n", c);
        t = -1;
    }
    c = count(9, 1, "a\nbcdeefsdf");
    if (c != 0)
    {
        printf("Test failed! str = \"bcdeefsdf\", substr=\"a\", expected 0, got %llu\n", c);
        t = -1;
    }
    return t;
}
#endif

int main()
{
#if defined DEBUG
    printf("test result: %d\n", test());
#endif
    size_t s1Len;
    printf("Enter length of substring S1 (which occurances will be counted in string S): ");
    scanf("%llu", &s1Len);

    char *str = malloc(s1Len * sizeof(char));
    printf("Enter substring S1: ");
    scanf("%s", str);

    size_t sLen;
    printf("Enter length of string S: ");
    scanf("%llu", &sLen);

    str = realloc(str, (s1Len + sLen + 1) * sizeof(char));
    printf("Enter string S: ");
    scanf("%s", str + s1Len + 1);

    str[s1Len] = '\n';

    printf("Number of occurances s1 in s: %llu\n", count(sLen, s1Len, str));

    free(str);
}