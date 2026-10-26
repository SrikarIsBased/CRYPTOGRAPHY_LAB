#include <stdio.h>
#include <string.h>
#include <ctype.h>

char sq[5][5];
int rowOf[26], colOf[26];

void readline(char *s, int n)
{
    if (fgets(s, n, stdin) == NULL)
    {
        s[0] = '\0';
        return;
    }
    s[strcspn(s, "\r\n")] = '\0';
}

void buildsquare(char *key)
{
    int used[26] = {0}, i, k = 0;
    char c;
    used['J' - 'A'] = 1;
    for (i = 0; key[i]; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            continue;
        c = toupper((unsigned char)key[i]);
        if (c == 'J')
            c = 'I';
        if (!used[c - 'A'])
        {
            used[c - 'A'] = 1;
            sq[k / 5][k % 5] = c;
            k++;
        }
    }
    for (c = 'A'; c <= 'Z'; c++)
        if (!used[c - 'A'])
        {
            used[c - 'A'] = 1;
            sq[k / 5][k % 5] = c;
            k++;
        }
    for (i = 0; i < 25; i++)
    {
        rowOf[sq[i / 5][i % 5] - 'A'] = i / 5;
        colOf[sq[i / 5][i % 5] - 'A'] = i % 5;
    }
    rowOf['J' - 'A'] = rowOf['I' - 'A'];
    colOf['J' - 'A'] = colOf['I' - 'A'];
}

int filter(char *in, char *out)
{
    int i, k = 0;
    char c;
    for (i = 0; in[i]; i++)
        if (isalpha((unsigned char)in[i]))
        {
            c = toupper((unsigned char)in[i]);
            out[k++] = (c == 'J') ? 'I' : c;
        }
    out[k] = '\0';
    return k;
}

int prepare(char *in, char *out)
{
    int i = 0, k = 0, n = strlen(in);
    char a, b;
    while (i < n)
    {
        a = in[i];
        b = (i + 1 < n) ? in[i + 1] : '\0';
        out[k++] = a;
        if (b == '\0' || a == b)
        {
            out[k++] = (a == 'X') ? 'Q' : 'X';
            i++;
        }
        else
        {
            out[k++] = b;
            i += 2;
        }
    }
    out[k] = '\0';
    return k;
}

void playfair(char *in, char *out, int mode)
{
    int i, r1, c1, r2, c2, d = (mode == 0) ? 1 : 4;
    for (i = 0; in[i]; i += 2)
    {
        r1 = rowOf[in[i] - 'A'];
        c1 = colOf[in[i] - 'A'];
        r2 = rowOf[in[i + 1] - 'A'];
        c2 = colOf[in[i + 1] - 'A'];
        if (r1 == r2)
        {
            out[i] = sq[r1][(c1 + d) % 5];
            out[i + 1] = sq[r2][(c2 + d) % 5];
        }
        else if (c1 == c2)
        {
            out[i] = sq[(r1 + d) % 5][c1];
            out[i + 1] = sq[(r2 + d) % 5][c2];
        }
        else
        {
            out[i] = sq[r1][c2];
            out[i + 1] = sq[r2][c1];
        }
    }
    out[i] = '\0';
}

void printpairs(char *label, char *s)
{
    int i;
    printf("%s", label);
    for (i = 0; s[i]; i += 2)
        printf("%c%c ", s[i], s[i + 1]);
    printf("\n");
}

int main()
{
    char line[512], key[512], pt[512], ft[512], pr[1024], ct[1024], dt[1024];
    int t, i, r, c;

    printf("===== PLAYFAIR CIPHER =====\n");
    printf("Enter key: ");
    readline(key, sizeof(key));
    buildsquare(key);

    printf("Key Matrix (I/J combined):\n");
    for (r = 0; r < 5; r++)
    {
        printf("   ");
        for (c = 0; c < 5; c++)
            printf("%c ", sq[r][c]);
        printf("\n");
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
        printf("Plaintext  : [%s]\n", pt);

        if (filter(pt, ft) == 0)
        {
            printf("No alphabets to encrypt\n");
            continue;
        }
        prepare(ft, pr);
        playfair(pr, ct, 0);
        playfair(ct, dt, 1);

        printf("Filtered   : %s\n", ft);
        printpairs("Digraphs   : ", pr);
        printpairs("Ciphertext : ", ct);
        printpairs("Decrypted  : ", dt);
        printf("Status     : %s\n", strcmp(pr, dt) == 0 ? "SUCCESS" : "MISMATCH");
    }

    return 0;
}
