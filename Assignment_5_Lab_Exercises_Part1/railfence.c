#include <stdio.h>
#include <string.h>

void readline(char *s, int n)
{
    if (fgets(s, n, stdin) == NULL)
    {
        s[0] = '\0';
        return;
    }
    s[strcspn(s, "\r\n")] = '\0';
}

void pattern(int n, int r, int *row)
{
    int i, cur = 0, dir = 1;
    for (i = 0; i < n; i++)
    {
        row[i] = cur;
        if (r == 1)
            continue;
        if (cur == 0)
            dir = 1;
        else if (cur == r - 1)
            dir = -1;
        cur += dir;
    }
}

void encrypt(char *in, char *out, int r)
{
    int n = strlen(in), row[512], i, k = 0, rr;
    pattern(n, r, row);
    for (rr = 0; rr < r; rr++)
        for (i = 0; i < n; i++)
            if (row[i] == rr)
                out[k++] = in[i];
    out[k] = '\0';
}

void decrypt(char *in, char *out, int r)
{
    int n = strlen(in), row[512], i, k = 0, rr;
    pattern(n, r, row);
    for (rr = 0; rr < r; rr++)
        for (i = 0; i < n; i++)
            if (row[i] == rr)
                out[i] = in[k++];
    out[n] = '\0';
}

int main()
{
    char line[512], pt[512], ct[512], dt[512];
    int t, i, r, n;

    printf("===== RAIL FENCE CIPHER =====\n");
    printf("Enter number of rails: ");
    readline(line, sizeof(line));
    if (sscanf(line, "%d", &r) != 1 || r < 2)
    {
        printf("Invalid key: number of rails must be at least 2\n");
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
        n = strlen(pt);
        printf("Plaintext  : [%s]\n", pt);
        if (n == 0)
        {
            printf("Empty input, nothing to encrypt\n");
            continue;
        }
        if (r >= n)
            printf("Note: rails >= length, text stays in one zigzag pass\n");
        encrypt(pt, ct, r);
        decrypt(ct, dt, r);
        printf("Ciphertext : [%s]\n", ct);
        printf("Decrypted  : [%s]\n", dt);
        printf("Status     : %s\n", strcmp(pt, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
