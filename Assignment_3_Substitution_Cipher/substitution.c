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

void shift(char *in, char *out, int k)
{
    int i;
    for (i = 0; in[i]; i++)
    {
        if (isupper((unsigned char)in[i]))
            out[i] = (char)((in[i] - 'A' + k) % 26 + 'A');
        else if (islower((unsigned char)in[i]))
            out[i] = (char)((in[i] - 'a' + k) % 26 + 'a');
        else
            out[i] = in[i];
    }
    out[i] = '\0';
}

int main()
{
    char line[512], pt[512], ct[512], dt[512];
    int t, i, n, k;

    printf("===== SUBSTITUTION CIPHER (KEY = INTEGER n) =====\n");
    printf("Enter key n: ");
    readline(line, sizeof(line));
    if (sscanf(line, "%d", &n) != 1)
    {
        printf("Invalid key: n must be an integer\n");
        return 0;
    }
    k = ((n % 26) + 26) % 26;
    printf("Effective shift = n mod 26 = %d\n", k);
    if (k == 0)
        printf("Warning: shift is 0, ciphertext will equal plaintext\n");

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
        shift(pt, ct, k);
        shift(ct, dt, (26 - k) % 26);
        printf("Plaintext  : [%s]\n", pt);
        printf("Ciphertext : [%s]\n", ct);
        printf("Decrypted  : [%s]\n", dt);
        printf("Status     : %s\n", strcmp(pt, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
