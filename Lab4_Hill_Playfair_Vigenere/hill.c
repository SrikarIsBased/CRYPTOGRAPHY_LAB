#include <stdio.h>
#include <string.h>
#include <ctype.h>

int K[2][2], Kinv[2][2];

void readline(char *s, int n)
{
    if (fgets(s, n, stdin) == NULL)
    {
        s[0] = '\0';
        return;
    }
    s[strcspn(s, "\r\n")] = '\0';
}

int mod26(int x)
{
    x %= 26;
    return x < 0 ? x + 26 : x;
}

int inverse26(int a)
{
    int x;
    for (x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return -1;
}

int filter(char *in, char *out)
{
    int i, k = 0;
    for (i = 0; in[i]; i++)
        if (isalpha((unsigned char)in[i]))
            out[k++] = toupper((unsigned char)in[i]);
    if (k % 2 == 1)
        out[k++] = 'X';
    out[k] = '\0';
    return k;
}

void hill(char *in, char *out, int M[2][2])
{
    int i, p0, p1;
    for (i = 0; in[i]; i += 2)
    {
        p0 = in[i] - 'A';
        p1 = in[i + 1] - 'A';
        out[i] = (char)(mod26(M[0][0] * p0 + M[0][1] * p1) + 'A');
        out[i + 1] = (char)(mod26(M[1][0] * p0 + M[1][1] * p1) + 'A');
    }
    out[i] = '\0';
}

int main()
{
    char line[512], pt[512], ft[512], ct[512], dt[512];
    int t, i, a, b, c, d, det, dinv, letters, k;

    printf("===== HILL CIPHER (2x2) =====\n");
    printf("Enter key matrix (4 integers a b c d): ");
    readline(line, sizeof(line));
    if (sscanf(line, "%d %d %d %d", &a, &b, &c, &d) != 4)
    {
        printf("Invalid key: enter exactly 4 integers\n");
        return 0;
    }
    K[0][0] = mod26(a);
    K[0][1] = mod26(b);
    K[1][0] = mod26(c);
    K[1][1] = mod26(d);

    det = mod26(K[0][0] * K[1][1] - K[0][1] * K[1][0]);
    dinv = inverse26(det);
    printf("Key Matrix      : [%d %d ; %d %d]\n", K[0][0], K[0][1], K[1][0], K[1][1]);
    printf("Determinant     : %d (mod 26)\n", det);
    if (dinv == -1)
    {
        printf("Key matrix is NOT invertible mod 26, choose another key\n");
        return 0;
    }

    Kinv[0][0] = mod26(dinv * K[1][1]);
    Kinv[0][1] = mod26(-dinv * K[0][1]);
    Kinv[1][0] = mod26(-dinv * K[1][0]);
    Kinv[1][1] = mod26(dinv * K[0][0]);
    printf("Inverse Matrix  : [%d %d ; %d %d]\n", Kinv[0][0], Kinv[0][1], Kinv[1][0], Kinv[1][1]);

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
        printf("Plaintext  : [%s]\n", pt);

        letters = 0;
        for (k = 0; pt[k]; k++)
            if (isalpha((unsigned char)pt[k]))
                letters++;
        if (letters == 0)
        {
            printf("No alphabets to encrypt\n");
            continue;
        }

        filter(pt, ft);
        hill(ft, ct, K);
        hill(ct, dt, Kinv);

        printf("Filtered   : %s%s\n", ft, (letters % 2) ? "  (X padded)" : "");
        printf("Ciphertext : %s\n", ct);
        printf("Decrypted  : %s\n", dt);
        printf("Status     : %s\n", strcmp(ft, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
