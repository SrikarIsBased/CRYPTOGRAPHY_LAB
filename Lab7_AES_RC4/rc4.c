#include <stdio.h>
#include <string.h>

unsigned char S[256];

void swap(unsigned char *a, unsigned char *b)
{
    unsigned char t = *a;
    *a = *b;
    *b = t;
}

void ksa(char *key)
{
    int i, j = 0, n = strlen(key);
    for (i = 0; i < 256; i++)
        S[i] = (unsigned char)i;
    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + (unsigned char)key[i % n]) % 256;
        swap(&S[i], &S[j]);
    }
}

void prga(unsigned char *in, unsigned char *out, unsigned char *ks, int len)
{
    int i = 0, j = 0, k;
    for (k = 0; k < len; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);
        ks[k] = S[(S[i] + S[j]) % 256];
        out[k] = in[k] ^ ks[k];
    }
}

int main()
{
    char pt[256], key[64];
    unsigned char ct[256], ks[256], dt[256];
    int i, len;

    printf("===== RC4 STREAM CIPHER =====\n");
    printf("Enter plaintext: ");
    scanf("%255s", pt);
    printf("Enter key: ");
    scanf("%63s", key);

    len = strlen(pt);
    printf("\nPlaintext length : %d characters\n", len);
    printf("Key length       : %d characters\n", (int)strlen(key));

    ksa(key);
    prga((unsigned char *)pt, ct, ks, len);

    printf("\n----- KEYSTREAM (hex) -----\n");
    for (i = 0; i < len; i++)
    {
        printf("%02X ", ks[i]);
        if (i % 16 == 15)
            printf("\n");
    }

    printf("\n\n----- ENCRYPTION -----\n");
    printf("Ciphertext (hex):\n");
    for (i = 0; i < len; i++)
    {
        printf("%02X ", ct[i]);
        if (i % 16 == 15)
            printf("\n");
    }

    ksa(key);
    prga(ct, dt, ks, len);
    dt[len] = '\0';

    printf("\n\n----- DECRYPTION -----\n");
    printf("Decrypted text: %s\n", dt);

    if (strcmp((char *)dt, pt) == 0)
        printf("\nDecrypted text matches plaintext -> RC4 SUCCESSFUL\n");
    else
        printf("\nDecrypted text does not match plaintext\n");

    return 0;
}
