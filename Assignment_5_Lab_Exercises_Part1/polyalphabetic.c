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

int cleankey(char *in, char *key)
{
    int i, k = 0;
    for (i = 0; in[i]; i++)
        if (isalpha((unsigned char)in[i]))
            key[k++] = toupper((unsigned char)in[i]);
    key[k] = '\0';
    return k;
}

void vigenere(char *in, char *out, char *key, int klen, int mode)
{
    int i, j = 0, sh;
    for (i = 0; in[i]; i++)
    {
        if (isalpha((unsigned char)in[i]))
        {
            sh = key[j % klen] - 'A';
            if (mode == 1)
                sh = 26 - sh;
            if (isupper((unsigned char)in[i]))
                out[i] = (char)((in[i] - 'A' + sh) % 26 + 'A');
            else
                out[i] = (char)((in[i] - 'a' + sh) % 26 + 'a');
            j++;
        }
        else
            out[i] = in[i];
    }
    out[i] = '\0';
}

int main()
{
    char line[512], key[512], pt[512], ct[512], dt[512];
    int t, i, klen, letters, k;

    printf("===== POLYALPHABETIC (VIGENERE) CIPHER =====\n");
    printf("Enter key: ");
    readline(line, sizeof(line));
    klen = cleankey(line, key);
    if (klen == 0)
    {
        printf("Invalid key: key must contain at least one alphabet\n");
        return 0;
    }
    printf("Key used : %s\n", key);

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

        letters = 0;
        for (k = 0; pt[k]; k++)
            if (isalpha((unsigned char)pt[k]))
                letters++;

        printf("Plaintext  : [%s]\n", pt);
        if (letters == 0)
        {
            printf("No alphabets to encrypt, text unchanged\n");
            printf("Ciphertext : [%s]\n", pt);
            continue;
        }

        vigenere(pt, ct, key, klen, 0);
        vigenere(ct, dt, key, klen, 1);

        printf("Ciphertext : [%s]\n", ct);
        printf("Decrypted  : [%s]\n", dt);
        printf("Status     : %s\n", strcmp(pt, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
