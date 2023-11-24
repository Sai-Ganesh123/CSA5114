#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency of each letter in the text
void calculateFrequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequency[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to perform an additive cipher frequency attack
void additiveCipherAttack(const char *ciphertext, int numPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Find the most frequent letter in the ciphertext (assumed to be 'E')
    int mostFrequentIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[mostFrequentIndex]) {
            mostFrequentIndex = i;
        }
    }

    // Calculate the potential key based on the shift of 'E' to 'E'
    int shift = (mostFrequentIndex + 26 - ('E' - 'A')) % 26;

    // Decrypt the ciphertext using the calculated shift
    printf("Possible plaintexts:\n");
    for (int i = 0; i < numPlaintexts; i++) {
        printf("%2d. ", i + 1);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            char decryptedChar = ciphertext[j];
            if (isalpha(decryptedChar)) {
                char base = islower(decryptedChar) ? 'a' : 'A';
                decryptedChar = (decryptedChar - base - shift + 26) % 26 + base;
            }
            printf("%c", decryptedChar);
        }
        printf("\n");
        shift = (shift + 1) % 26; // Try the next shift
    }
}

int main() {
    char ciphertext[] = "YKIXKZ SKKYKX";
    int numPlaintexts = 10;

    additiveCipherAttack(ciphertext, numPlaintexts);

    return 0;
}
