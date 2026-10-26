#include <stdio.h>
#include <string.h>
#include <ctype.h>

char enc[26], dec[26];

void readline(char *s, int n)
{
    if (fgets(s, n, stdin) == NULL)
    {
        s[0] = '\0';
        return;
    }
    s[strcspn(s, "\r\n")] = '\0';
}

int setkey(char *key)
{
    int i, seen[26] = {0}, c;
    if (strlen(key) != 26)
        return 0;
    for (i = 0; i < 26; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            return 0;
        c = toupper((unsigned char)key[i]) - 'A';
        if (seen[c])
            return 0;
        seen[c] = 1;
        enc[i] = (char)('A' + c);
        dec[c] = (char)('A' + i);
    }
    return 1;
}

void apply(char *in, char *out, char *map)
{
    int i;
    for (i = 0; in[i]; i++)
    {
        if (isupper((unsigned char)in[i]))
            out[i] = map[in[i] - 'A'];
        else if (islower((unsigned char)in[i]))
            out[i] = (char)tolower(map[in[i] - 'a']);
        else
            out[i] = in[i];
    }
    out[i] = '\0';
}

int main()
{
    char line[512], key[512], pt[512], ct[512], dt[512];
    int t, i;

    printf("===== MONOALPHABETIC CIPHER =====\n");
    printf("Enter 26-letter key: ");
    readline(key, sizeof(key));
    if (!setkey(key))
    {
        printf("Invalid key: must contain all 26 letters exactly once\n");
        return 0;
    }
    printf("Plain  : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher : %.26s\n", enc);

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
        apply(pt, ct, enc);
        apply(ct, dt, dec);
        printf("Plaintext  : [%s]\n", pt);
        printf("Ciphertext : [%s]\n", ct);
        printf("Decrypted  : [%s]\n", dt);
        printf("Status     : %s\n", strcmp(pt, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
