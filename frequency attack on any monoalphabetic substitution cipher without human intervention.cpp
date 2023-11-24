#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// English letter frequencies
const double englishFrequencies[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0009, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(const char *ciphertext, double *frequency) {
    int totalLetters = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
            totalLetters++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequency[i] /= totalLetters;
    }
}

// Function to calculate the chi-square score
double chiSquareScore(const double *observed, const double *expected) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double diff = observed[i] - expected[i];
        score += (diff * diff) / expected[i];
    }
    return score;
}

// Function to perform a letter frequency attack
void letterFrequencyAttack(const char *ciphertext, int numPlaintexts) {
    double observedFrequency[ALPHABET_SIZE] = {0.0};
    calculateFrequency(ciphertext, observedFrequency);

    printf("Possible plaintexts:\n");

    // Try all possible shifts
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        printf("%2d. ", shift + 1);

        // Decrypt the ciphertext using the current shift
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                char decryptedChar = 'A' + (ciphertext[i] - 'A' + shift) % ALPHABET_SIZE;
                printf("%c", decryptedChar);
            } else {
                printf("%c", ciphertext[i]);
            }
        }

        // Calculate the chi-square score and print
        double chiSquare = chiSquareScore(observedFrequency, englishFrequencies);
        printf(" (Chi-Square: %.4f)\n", chiSquare);
    }
}

int main() {
    char ciphertext[] = "VQREQFGT";
    int numPlaintexts = 10;

    letterFrequencyAttack(ciphertext, numPlaintexts);

    return 0;
}
