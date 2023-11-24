#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Include for isalpha function

#define ALPHABET_SIZE 26

// Function to calculate the modulo inverse of a number a with respect to m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function to encrypt a plaintext character using the affine Caesar cipher
char encryptCharacter(int a, int b, char p) {
    if (isalpha(p)) {
        int base = islower(p) ? 'a' : 'A';
        return (a * (p - base) + b) % ALPHABET_SIZE + base;
    }
    return p;
}

// Function to decrypt a ciphertext character using the affine Caesar cipher
char decryptCharacter(int a, int b, char c) {
    if (isalpha(c)) {
        int base = islower(c) ? 'a' : 'A';
        int modInvA = modInverse(a, ALPHABET_SIZE);
        if (modInvA == -1) {
            printf("Inverse doesn't exist. Decryption is not possible.\n");
            exit(1);
        }
        return (modInvA * (c - base - b + ALPHABET_SIZE)) % ALPHABET_SIZE + base;
    }
    return c;
}

// Function to perform the affine Caesar cipher encryption
void encryptAffineCaesar(int a, int b, const char *plaintext, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = encryptCharacter(a, b, plaintext[i]);
    }
    ciphertext[i] = '\0';  // Terminate the string
}

// Function to perform the affine Caesar cipher decryption
void decryptAffineCaesar(int a, int b, const char *ciphertext, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = decryptCharacter(a, b, ciphertext[i]);
    }
    plaintext[i] = '\0';  // Terminate the string
}

int main() {
    int a = 5; // Choose a value for 'a'
    int b = 8; // Choose a value for 'b'

    char plaintext[] = "HELLO WORLD";
    char ciphertext[100];
    char decryptedText[100];

    encryptAffineCaesar(a, b, plaintext, ciphertext);
    printf("Encrypted: %s\n", ciphertext);

    decryptAffineCaesar(a, b, ciphertext, decryptedText);
    printf("Decrypted: %s\n", decryptedText);

    return 0;
}
