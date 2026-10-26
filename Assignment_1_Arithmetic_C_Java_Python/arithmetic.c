#include <stdio.h>

int main()
{
    int t, i;
    long long a, b;

    printf("===== ARITHMETIC OPERATIONS IN C =====\n");
    printf("Enter number of test cases: ");
    if (scanf("%d", &t) != 1 || t <= 0)
    {
        printf("Invalid number of test cases\n");
        return 0;
    }

    for (i = 1; i <= t; i++)
    {
        printf("\nTest Case %d\n", i);
        printf("Enter first number a: ");
        if (scanf("%lld", &a) != 1)
        {
            printf("Invalid input\n");
            return 0;
        }
        printf("Enter second number b: ");
        if (scanf("%lld", &b) != 1)
        {
            printf("Invalid input\n");
            return 0;
        }

        printf("Addition       : %lld + %lld = %lld\n", a, b, a + b);
        printf("Subtraction    : %lld - %lld = %lld\n", a, b, a - b);
        printf("Multiplication : %lld * %lld = %lld\n", a, b, a * b);
        if (b == 0)
        {
            printf("Division       : Not possible (division by zero)\n");
            printf("Modulus        : Not possible (division by zero)\n");
        }
        else
        {
            printf("Division       : %lld / %lld = %.4f\n", a, b, (double)a / b);
            printf("Modulus        : %lld %% %lld = %lld\n", a, b, a % b);
        }
    }

    return 0;
}
