#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// #define DEBUG 1

typedef enum
{
    OK,
    IncorrectBinaryNumber
} Error;

Error convertNumberFromBinToOctalForm(char *numberInBinForm, char *numberInOctalForm)
{
    short lastIndexOfBinNumber = strlen(numberInBinForm) - 1;
    short lastIndexOfOctalNumber = lastIndexOfBinNumber / 3 + 1;
    short curOffset = 8;
    while (lastIndexOfBinNumber >= 0)
    {
        if (curOffset == 8)
        {
            curOffset = 1;
            --lastIndexOfOctalNumber;
            numberInOctalForm[lastIndexOfOctalNumber] = '0';
        }
        switch (numberInBinForm[lastIndexOfBinNumber])
        {
        case '0':
            break;
        case '1':
            numberInOctalForm[lastIndexOfOctalNumber] += curOffset * (numberInBinForm[lastIndexOfBinNumber] - '0');
            break;
        default:
            return IncorrectBinaryNumber;
        }
        --lastIndexOfBinNumber;
        curOffset = curOffset << 1;
    }
    return OK;
}

#ifdef DEBUG
bool test1()
{
    char numberInBinForm[257] = {0};
    char numberInOctalForm[86] = {0};
    strcpy(numberInBinForm, "110101");
    convertNumberFromBinToOctalForm(numberInBinForm, numberInOctalForm);
    return strcmp(numberInOctalForm, "65") == 0;
}

bool test2()
{
    char numberInBinForm[257] = {0};
    char numberInOctalForm[86] = {0};
    strcpy(numberInBinForm, "10011");
    convertNumberFromBinToOctalForm(numberInBinForm, numberInOctalForm);
    return strcmp(numberInOctalForm, "23") == 0;
}

bool test3()
{
    char numberInBinForm[257] = {0};
    char numberInOctalForm[86] = {0};
    strcpy(numberInBinForm, "1111001010001010110111001000011111000101011111011011001010111001010101100010011111100110001101100101100011011001101011001011001000010011110110010110110111100110110000100011100110000011110110111010010100010100000001100000101001111101010011110100010111011011");
    convertNumberFromBinToOctalForm(numberInBinForm, numberInOctalForm);
    return strcmp(numberInOctalForm, "17121267103705373312712542374615454331531310236626674660434603667224240140517523642733") == 0;
}

bool test4()
{
    char numberInBinForm[257] = {0};
    char numberInOctalForm[86] = {0};
    strcpy(numberInBinForm, "1010102");
    return convertNumberFromBinToOctalForm(numberInBinForm, numberInOctalForm) == IncorrectBinaryNumber;
}
#endif

int main()
{
#ifdef DEBUG
    printf("Test 1 result: %s\n", test1() ? "OK" : "FAIL");
    printf("Test 2 result: %s\n", test2() ? "OK" : "FAIL");
    printf("Test 3 result: %s\n", test3() ? "OK" : "FAIL");
    printf("Test 4 result: %s\n", test4() ? "OK" : "FAIL");
#endif
    char numberInBinForm[257] = {0};
    printf("Enter a number in binary form (no longer than 256 symbols): ");
    scanf("%256s", numberInBinForm);
    char numberInOctalForm[86] = {0};
    if (convertNumberFromBinToOctalForm(numberInBinForm, numberInOctalForm) == IncorrectBinaryNumber)
    {
        printf("Incorrect binary number!\n");
        return 0;
    }
    printf("Number in octal form: %s\n", numberInOctalForm);
    return 0;
}