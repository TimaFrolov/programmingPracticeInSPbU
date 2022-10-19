#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define DEBUG 1

bool isPalindrome(char *string)
{
    char *first = string,
         *last = string + strlen(string) - 1;

    while (first < last && *first == *last)
    {
        ++first;
        --last;
    }
    
    return first >= last;
}

#ifdef DEBUG
bool test1()
{
    char *str = "abcdcba";
    return isPalindrome(str);
}

bool test2()
{
    char *str = "abcdcda";
    return !isPalindrome(str);
}

bool test3()
{
    char *str = "abba";
    return isPalindrome(str);
}

bool test4()
{
    char *str = "";
    return isPalindrome(str);
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test 1 %s\n", (test1() ? "succeeded" : "failed"));
    printf("Test 2 %s\n", (test2() ? "succeeded" : "failed"));
    printf("Test 3 %s\n", (test3() ? "succeeded" : "failed"));
    printf("Test 4 %s\n", (test4() ? "succeeded" : "failed"));
#endif

    printf("Enter length of string (natural number): ");
    size_t len = 0;
    int scanResult = scanf("%lu", &len);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Wrong input! Please enter natural number: ");
        scanResult = scanf("%lu", &len);
    }

    char *str = calloc(len + 1, sizeof(char));
    if (str == NULL)
    {
        printf("Error allocating memory for array!\n");
        return -1;
    }

    while (getc(stdin) != '\n')
    {
    }

    for (size_t i = 0; i < len; ++i)
    {
        str[i] = getc(stdin);
    }
    printf(isPalindrome(str) ? "Given string is palindrome!\n" : "Given string is not palindrome :(\n");

    free(str);
    return 0;
}