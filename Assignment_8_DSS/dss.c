#include <stdio.h>

long long power(long long b, long long e, long long m)
{
    long long r = 1;
    b = b % m;
    while (e > 0)
    {
        if (e & 1)
            r = (r * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return r;
}

long long modinv(long long a, long long m)
{
    long long m0 = m, t, q, x0 = 0, x1 = 1;
    a = a % m;
    if (m == 1)
        return 0;
    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main()
{
    long long p, q, h, g, x, y, k, hm, hr, r, s, w, u1, u2, v;

    printf("===== DIGITAL SIGNATURE STANDARD (DSS) =====\n");
    printf("Enter prime p: ");
    scanf("%lld", &p);
    printf("Enter prime q (q divides p-1): ");
    scanf("%lld", &q);

    if ((p - 1) % q != 0)
    {
        printf("Invalid input: q must divide p-1\n");
        return 0;
    }

    printf("Enter h (1 < h < p-1): ");
    scanf("%lld", &h);
    g = power(h, (p - 1) / q, p);
    if (g <= 1)
    {
        printf("Invalid h: g must be greater than 1\n");
        return 0;
    }

    printf("Enter private key x (0 < x < q): ");
    scanf("%lld", &x);
    printf("Enter random secret k (0 < k < q): ");
    scanf("%lld", &k);
    printf("Enter hash of message H(M) at sender: ");
    scanf("%lld", &hm);
    printf("Enter hash of message H(M') at receiver: ");
    scanf("%lld", &hr);

    y = power(g, x, p);

    printf("\n----- KEY GENERATION -----\n");
    printf("g = h^((p-1)/q) mod p = %lld\n", g);
    printf("Public Key  (p, q, g, y) = (%lld, %lld, %lld, %lld)\n", p, q, g, y);
    printf("Private Key x = %lld\n", x);

    r = power(g, k, p) % q;
    s = (modinv(k, q) * ((hm + x * r) % q)) % q;

    if (r == 0 || s == 0)
    {
        printf("r or s is zero, choose another k\n");
        return 0;
    }

    printf("\n----- SIGNING -----\n");
    printf("r = (g^k mod p) mod q = %lld\n", r);
    printf("s = (k^-1 * (H(M) + x*r)) mod q = %lld\n", s);
    printf("Signature (r, s) = (%lld, %lld)\n", r, s);

    w = modinv(s, q);
    u1 = (hr * w) % q;
    u2 = (r * w) % q;
    v = ((power(g, u1, p) * power(y, u2, p)) % p) % q;

    printf("\n----- VERIFICATION -----\n");
    printf("w  = s^-1 mod q = %lld\n", w);
    printf("u1 = (H(M') * w) mod q = %lld\n", u1);
    printf("u2 = (r * w) mod q = %lld\n", u2);
    printf("v  = ((g^u1 * y^u2) mod p) mod q = %lld\n", v);

    if (v == r)
        printf("\nv = r -> SIGNATURE IS VALID\n");
    else
        printf("\nv != r -> SIGNATURE IS INVALID\n");

    return 0;
}
