#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

// Function to perform a letter frequency attack
void letterFrequencyAttack(const char *ciphertext, int numPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Create a copy of the frequency array to sort and find most frequent letters
    int sortedFrequency[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedFrequency[i] = frequency[i];
    }

    // Sort the frequency array in descending order
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (sortedFrequency[j] < sortedFrequency[j + 1]) {
                int temp = sortedFrequency[j];
                sortedFrequency[j] = sortedFrequency[j + 1];
                sortedFrequency[j + 1] = temp;
            }
        }
    }

    // Calculate the key using the most frequent letters in English
    char key[ALPHABET_SIZE];
    char mostFrequentLetters[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = ' ';
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int index = frequency[i];
        if (index >= 0 && index < ALPHABET_SIZE) {
            key[index] = mostFrequentLetters[i];
        }
    }

    // Decrypt the ciphertext using the key
    printf("Possible plaintexts:\n");
    for (int i = 0; i < numPlaintexts; i++) {
        printf("%2d. ", i + 1);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            if (ciphertext[j] >= 'A' && ciphertext[j] <= 'Z') {
                printf("%c", key[ciphertext[j] - 'A']);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[] = "VQREQFGT";
    int numPlaintexts = 10;

    letterFrequencyAttack(ciphertext, numPlaintexts);

    return 0;
}
