#include <stdio.h>

int isPrime(long long n)
{
    long long i;
    if (n < 2)
        return 0;
    if (n < 4)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

int main()
{
    int t, i;
    long long n;

    printf("===== PRIME NUMBER CHECK (OPTIMAL TIME AND MEMORY) =====\n");
    printf("Enter number of test cases: ");
    scanf("%d", &t);

    for (i = 1; i <= t; i++)
    {
        printf("\nTest Case %d\n", i);
        printf("Enter a number: ");
        scanf("%lld", &n);

        if (isPrime(n))
            printf("Result: %lld is a PRIME number\n", n);
        else
            printf("Result: %lld is NOT a prime number\n", n);
    }

    return 0;
}
