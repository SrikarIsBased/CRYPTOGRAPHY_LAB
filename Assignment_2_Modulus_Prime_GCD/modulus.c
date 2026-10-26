#include <stdio.h>

long long modulus(long long a, long long b)
{
    return a - (a / b) * b;
}

int main()
{
    int t, i;
    long long a, b;

    printf("===== MODULUS WITHOUT USING %% OPERATOR =====\n");
    printf("Enter number of test cases: ");
    scanf("%d", &t);

    for (i = 1; i <= t; i++)
    {
        printf("\nTest Case %d\n", i);
        printf("Enter dividend a: ");
        scanf("%lld", &a);
        printf("Enter divisor b: ");
        scanf("%lld", &b);

        if (b == 0)
        {
            printf("Error: divisor cannot be zero\n");
            continue;
        }

        printf("Quotient  = a / b = %lld\n", a / b);
        printf("Remainder = a - (a / b) * b = %lld\n", modulus(a, b));
        printf("Result: %lld mod %lld = %lld\n", a, b, modulus(a, b));
    }

    return 0;
}
