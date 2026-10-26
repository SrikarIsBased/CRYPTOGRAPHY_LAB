#include <stdio.h>
#include <string.h>

typedef unsigned long long u64;

int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

int FP[64] = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

int E[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13,
             12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
             24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

int P[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
             2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

int PC1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
               10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
               14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

int PC2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
               23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
               41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
               44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

int SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

int S[8][64] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
     4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
     0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
     13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
     10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
     4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
     9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
     1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
     7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

u64 K[16];

u64 permute(u64 in, int *table, int n, int inbits)
{
    u64 out = 0;
    int i;
    for (i = 0; i < n; i++)
        out = (out << 1) | ((in >> (inbits - table[i])) & 1ULL);
    return out;
}

u64 rotl28(u64 x, int s)
{
    return ((x << s) | (x >> (28 - s))) & 0xFFFFFFFULL;
}

void keyschedule(u64 key)
{
    u64 cd = permute(key, PC1, 56, 64);
    u64 c = (cd >> 28) & 0xFFFFFFFULL, d = cd & 0xFFFFFFFULL;
    int i;
    for (i = 0; i < 16; i++)
    {
        c = rotl28(c, SHIFTS[i]);
        d = rotl28(d, SHIFTS[i]);
        K[i] = permute((c << 28) | d, PC2, 48, 56);
    }
}

u64 f(u64 r, u64 k)
{
    u64 x = permute(r, E, 48, 32) ^ k, out = 0;
    int i, b, row, col;
    for (i = 0; i < 8; i++)
    {
        b = (int)((x >> (42 - 6 * i)) & 0x3F);
        row = ((b >> 4) & 2) | (b & 1);
        col = (b >> 1) & 0xF;
        out = (out << 4) | (u64)S[i][row * 16 + col];
    }
    return permute(out, P, 32, 32);
}

u64 des(u64 block, int mode)
{
    u64 x = permute(block, IP, 64, 64);
    u64 l = x >> 32, r = x & 0xFFFFFFFFULL, t;
    int i;
    for (i = 0; i < 16; i++)
    {
        t = r;
        r = l ^ f(r, K[mode ? 15 - i : i]);
        l = t;
    }
    return permute((r << 32) | l, FP, 64, 64);
}

u64 load(unsigned char *p)
{
    u64 v = 0;
    int i;
    for (i = 0; i < 8; i++)
        v = (v << 8) | p[i];
    return v;
}

void store(u64 v, unsigned char *p)
{
    int i;
    for (i = 7; i >= 0; i--)
    {
        p[i] = (unsigned char)(v & 0xFF);
        v >>= 8;
    }
}

int main()
{
    char pt[256], kin[256];
    unsigned char key[8] = {0}, buf[264], ct[264], dt[264];
    int i, n, len, pad;

    printf("===== DES (DATA ENCRYPTION STANDARD) =====\n");
    printf("Enter plaintext: ");
    if (scanf("%255s", pt) != 1)
        return 0;
    printf("Enter password (key): ");
    if (scanf("%255s", kin) != 1)
        return 0;

    n = strlen(kin);
    if (n > 8)
        printf("Note: key longer than 8 characters, first 8 used\n");
    if (n < 8)
        printf("Note: key shorter than 8 characters, padded with zero bytes\n");
    memcpy(key, kin, n > 8 ? 8 : n);

    len = strlen(pt);
    pad = 8 - len % 8;
    memcpy(buf, pt, len);
    for (i = len; i < len + pad; i++)
        buf[i] = (unsigned char)pad;
    len += pad;

    printf("\nPlaintext length : %d characters\n", (int)strlen(pt));
    printf("Padded length    : %d bytes (%d blocks)\n", len, len / 8);
    printf("Key (64-bit hex) : ");
    for (i = 0; i < 8; i++)
        printf("%02X", key[i]);
    printf("\n");

    keyschedule(load(key));
    printf("\n----- ROUND KEYS (48-bit) -----\n");
    for (i = 0; i < 16; i++)
        printf("K%-2d = %012llX%s", i + 1, K[i], (i % 2) ? "\n" : "    ");

    for (i = 0; i < len; i += 8)
        store(des(load(buf + i), 0), ct + i);

    printf("\n----- ENCRYPTION -----\n");
    printf("Ciphertext (hex):\n");
    for (i = 0; i < len; i++)
    {
        printf("%02X", ct[i]);
        if (i % 8 == 7)
            printf(i % 32 == 31 ? "\n" : " ");
    }
    if (len % 32)
        printf("\n");

    for (i = 0; i < len; i += 8)
        store(des(load(ct + i), 1), dt + i);
    pad = dt[len - 1];
    dt[len - pad] = '\0';

    printf("\n----- DECRYPTION -----\n");
    printf("Decrypted text: %s\n", dt);
    if (strcmp((char *)dt, pt) == 0)
        printf("\nDecrypted text matches plaintext -> DES SUCCESSFUL\n");
    else
        printf("\nDecrypted text does not match plaintext\n");

    return 0;
}
