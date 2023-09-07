#include <stdio.h>

int extended_gcd(int a, int b, int *x, int *y) 
{
    // Base case
    if (a == 0) 
	{
        *x = 0;
        *y = 1;
        return b;
    }

    // Recursive case
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int main() 
{
    int a, b, x, y;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    int gcd = extended_gcd(a, b, &x, &y);

    printf("GCD of %d and %d is %d\n", a, b, gcd);
    printf("Coefficients x and y are: %d %d\n", x, y);

    return 0;
}

