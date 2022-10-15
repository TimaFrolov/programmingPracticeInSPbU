#include <stdio.h>
#include <locale.h>

void print_binary(int number)
{
    unsigned int n = 1 << 31;
    while (n)
    {
        printf(n & number ? "1" : "0");
        n >>= 1;
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

    printf("Двоичное представление первого числа: ");
    print_binary(firstNumber);
    printf("\n");
    printf("Двоичное представление второго числа: ");
    print_binary(secondNumber);
    printf("\n");
    printf("Двоичное представление суммы чисел:   ");
    print_binary(firstNumber + secondNumber);
    printf("\n");
    printf("Сумма чисел: %d\n", firstNumber + secondNumber);
}