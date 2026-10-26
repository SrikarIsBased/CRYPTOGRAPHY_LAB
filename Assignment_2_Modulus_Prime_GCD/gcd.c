#include <stdio.h>

long long gcd(long long a, long long b)
{
    long long r;
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main()
{
    int t, i;
    long long a, b;

    printf("===== GCD OF TWO NUMBERS (EUCLIDEAN ALGORITHM) =====\n");
    printf("Enter number of test cases: ");
    scanf("%d", &t);

    for (i = 1; i <= t; i++)
    {
        printf("\nTest Case %d\n", i);
        printf("Enter first number a: ");
        scanf("%lld", &a);
        printf("Enter second number b: ");
        scanf("%lld", &b);

        if (a == 0 && b == 0)
        {
            printf("GCD is undefined for 0 and 0\n");
            continue;
        }

        printf("Result: GCD(%lld, %lld) = %lld\n", a, b, gcd(a, b));
    }

    return 0;
}
