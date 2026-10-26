#include <stdio.h>
#include <string.h>
#include <ctype.h>

void readline(char *s, int n)
{
    if (fgets(s, n, stdin) == NULL)
    {
        s[0] = '\0';
        return;
    }
    s[strcspn(s, "\r\n")] = '\0';
}

int order(char *key, int *ord)
{
    int n = strlen(key), i, j, t;
    for (i = 0; i < n; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            return 0;
        ord[i] = i;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (toupper((unsigned char)key[ord[j]]) > toupper((unsigned char)key[ord[j + 1]]))
            {
                t = ord[j];
                ord[j] = ord[j + 1];
                ord[j + 1] = t;
            }
    return n;
}

void encrypt(char *in, char *out, char *key)
{
    int ord[64], c = order(key, ord), n = strlen(in), i, r, k = 0, col;
    for (i = 0; i < c; i++)
    {
        col = ord[i];
        for (r = col; r < n; r += c)
            out[k++] = in[r];
    }
    out[k] = '\0';
}

void decrypt(char *in, char *out, char *key)
{
    int ord[64], c = order(key, ord), n = strlen(in), i, r, k = 0, col;
    for (i = 0; i < c; i++)
    {
        col = ord[i];
        for (r = col; r < n; r += c)
            out[r] = in[k++];
    }
    out[n] = '\0';
}

int main()
{
    char line[512], k1[64], k2[64], pt[512], mid[512], ct[512], d1[512], dt[512];
    int t, i, ord[64];

    printf("===== DOUBLE COLUMNAR TRANSPOSITION CIPHER =====\n");
    printf("Enter first key: ");
    readline(k1, sizeof(k1));
    printf("Enter second key: ");
    readline(k2, sizeof(k2));
    if (strlen(k1) < 2 || strlen(k2) < 2 || !order(k1, ord) || !order(k2, ord))
    {
        printf("Invalid key: keys must be alphabetic with at least 2 letters\n");
        return 0;
    }

    printf("Enter number of test cases: ");
    readline(line, sizeof(line));
    if (sscanf(line, "%d", &t) != 1 || t <= 0)
    {
        printf("Invalid number of test cases\n");
        return 0;
    }

    for (i = 1; i <= t; i++)
    {
        printf("\nTest Case %d\n", i);
        printf("Enter plaintext: ");
        readline(pt, sizeof(pt));
        printf("Plaintext   : [%s]\n", pt);
        if (strlen(pt) == 0)
        {
            printf("Empty input, nothing to encrypt\n");
            continue;
        }
        encrypt(pt, mid, k1);
        encrypt(mid, ct, k2);
        decrypt(ct, d1, k2);
        decrypt(d1, dt, k1);
        printf("After key 1 : [%s]\n", mid);
        printf("Ciphertext  : [%s]\n", ct);
        printf("Decrypted   : [%s]\n", dt);
        printf("Status      : %s\n", strcmp(pt, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
