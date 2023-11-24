#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 26

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

// Function to perform matrix multiplication
void matrixMultiply(int key[2][2], int input[2], int result[2]) {
    for (int i = 0; i < 2; i++) {
        result[i] = 0;
        for (int j = 0; j < 2; j++) {
            result[i] += key[i][j] * input[j];
        }
        result[i] %= MOD;
    }
}

// Function to perform the known-plaintext attack
void knownPlaintextAttack(int key[2][2], int plaintext[2], int ciphertext[2]) {
    int inverseKey[2][2];
    int determinant = key[0][0] * key[1][1] - key[0][1] * key[1][0];

    int modInvDet = modInverse(determinant, MOD);
    if (modInvDet == -1) {
        printf("Inverse doesn't exist. Attack failed.\n");
        return;
    }

    inverseKey[0][0] = key[1][1];
    inverseKey[0][1] = -key[0][1];
    inverseKey[1][0] = -key[1][0];
    inverseKey[1][1] = key[0][0];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverseKey[i][j] = (inverseKey[i][j] * modInvDet + MOD) % MOD;
        }
    }

    matrixMultiply(inverseKey, ciphertext, plaintext);
}

int main() {
    int key[2][2] = {{6, 24}, {13, 16}}; // Example 2x2 matrix key
    int plaintext[2] = {2, 19};           // Example known plaintext
    int ciphertext[2];                    // Corresponding ciphertext

    // Encrypt the known plaintext to get the corresponding ciphertext
    matrixMultiply(key, plaintext, ciphertext);

    printf("Known Plaintext: %c%c\n", 'A' + plaintext[0], 'A' + plaintext[1]);
    printf("Ciphertext: %c%c\n", 'A' + ciphertext[0], 'A' + ciphertext[1]);

    // Perform the known-plaintext attack to retrieve the key
    knownPlaintextAttack(key, plaintext, ciphertext);

    printf("Recovered Key:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%2d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}
