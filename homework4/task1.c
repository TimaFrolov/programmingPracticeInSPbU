#include <stdio.h>
#include <locale.h>

typedef struct
{
    unsigned char bit[32];
} BinNumber;

BinNumber intToNumber(int number)
{
    BinNumber num = {bit : {0}};
    for (unsigned int n = 1 << 31, i = 31; n > 0; n >>= 1, --i)
    {
        num.bit[i] = n & number ? 1 : 0;
    }
    return num;
}

int binNumberToInt(BinNumber number)
{
    int num = 0;
    for (unsigned int n = 0; n < 32; ++n)
    {
        num |= (number.bit[n]) << n;
    }
    return num;
}

BinNumber sumBitNumbers(BinNumber number1, BinNumber number2)
{
    BinNumber answer = {bit : {0}};
    answer.bit[0] = number1.bit[0] ^ number2.bit[0];
    unsigned char t = number1.bit[0] && number2.bit[0];
    for (unsigned int n = 1; n < 31; ++n)
    {
        answer.bit[n] = number1.bit[n] ^ number2.bit[n] ^ t;
        t = (number1.bit[n] + number2.bit[n] + t) >= 2;
    }
    return answer;
}

void printBitNumber(BinNumber number)
{
    for (signed char i = 31; i >= 0; --i)
    {
        printf("%i", number.bit[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "Ru.866");

    int firstNumber = 0, secondNumber = 0;
    printf("Введите число: ");
    int scanResult = scanf("%d", &firstNumber);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Некорректный ввод! Пожалуйста, введите число: ");
        scanResult = scanf("%d", &firstNumber);
    }

    printf("Введите ещё одно число: ");
    scanResult = scanf("%d", &secondNumber);
    while (scanResult == 0)
    {
        scanf("%*[^\n]");
        printf("Некорректный ввод! Пожалуйста, введите число: ");
        scanResult = scanf("%d", &secondNumber);
    }

    BinNumber firstBitNumber = intToNumber(firstNumber);
    BinNumber secondBitNumber = intToNumber(secondNumber);
    BinNumber sumOfBitNumbers = sumBitNumbers(firstBitNumber, secondBitNumber);

    printf("Двоичное представление первого числа: ");
    printBitNumber(firstBitNumber);
    printf("\n");
    printf("Двоичное представление второго числа: ");
    printBitNumber(secondBitNumber);
    printf("\n");
    printf("Двоичное представление суммы чисел:   ");
    printBitNumber(sumOfBitNumbers);
    printf("\n");
    printf("Сумма чисел: %d\n", binNumberToInt(sumOfBitNumbers));

    return 0;
}