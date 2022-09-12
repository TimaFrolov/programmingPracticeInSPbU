#include <stdio.h>

float f(float x)
{
    const float x2 = x * x;
    return (x2 + 1) * (x2 + x) + 1;
}

int main()
{
    float x;
    printf("Enter x: ");
    scanf("%f", &x);
    printf("x^4 + x^3 + x^2 + x + 1 = %f\n", f(x));
}