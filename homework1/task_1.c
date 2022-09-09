#include <stdio.h>

int f(int x)
{
    const int x2 = x * x;
    return (x2 + 1) * (x2 + x) + 1;
}

int main()
{
    int x;
    printf("Enter x: ");
    scanf("%d", &x);
    printf("x^4 + x^3 + x^2 + x + 1 = %d\n", f(x));
}