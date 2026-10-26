# Cryptography Lab

Lab programs by **Badam Srikar** (Regd. No: 2024089837), GITAM University.

| # | Folder | Programs |
|---|---|---|
| 1 | `Assignment_1_Arithmetic_C_Java_Python` | Arithmetic operations in C, Java and Python |
| 2 | `Assignment_2_Modulus_Prime_GCD` | Modulus without % operator, Prime number (O(sqrt n) time, O(1) memory), GCD |
| 3 | `Assignment_3_Substitution_Cipher` | Substitution cipher with integer key n |
| 4 | `Assignment_4_Hill_Playfair_Polyalphabetic` | Hill (2x2), Playfair, Polyalphabetic (Vigenere) |
| 5 | `Assignment_5_Lab_Exercises_Part1` | Monoalphabetic, Caesar, Polyalphabetic, Hill, Playfair, Rail Fence, Double Columnar Transposition |
| 6 | `Assignment_6_DES` | DES (64-bit block, 16 rounds) |
| 7 | `Assignment_7_AES_RC4` | AES-128 and RC4 |
| 8 | `Assignment_8_DSS` | Digital Signature Standard |

## How to run

C:

```
gcc program.c -o program
program
```

Java:

```
javac Arithmetic.java
java Arithmetic
```

Python:

```
python arithmetic.py
```

## Common test cases for the cipher programs

```
BADAM SRIKAR
SITA$RAMA
            ABC
SEETHA
SITA123$$
GITAM UNIVERSITY
2024089837
```

Every cipher program reads input with `fgets`, so spaces and leading spaces are kept. Special characters and digits are either kept in place (substitution, Caesar, monoalphabetic, Vigenere, rail fence, columnar) or skipped (Hill, Playfair). Invalid keys are rejected, and every test case is decrypted and checked, printing SUCCESS or MISMATCH.

## Keys used

| Program | Key |
|---|---|
| Substitution | any integer n (negative and values above 26 are reduced mod 26) |
| Caesar | 3 |
| Monoalphabetic | QWERTYUIOPASDFGHJKLZXCVBNM |
| Polyalphabetic | DECEPTIVE |
| Hill | 3 3 2 5 |
| Playfair | MONARCHY |
| Rail Fence | 3 rails |
| Double Columnar | ZEBRAS, STRIPE |
| DES | BADAMSRIKAR (first 8 characters used) |
| AES / RC4 | BADAMSRIKAR |

## Given inputs

- DES: `WELCOMETOGITAMUNIVERSITYVISAKHAPATNAM`
- AES / RC4: `GITAMUNIVERSITYISDEEMEDTOBEUNIVERSITY`
