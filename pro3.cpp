#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void encrypt(char message[], char substitution_table[]) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            if (isupper(message[i])) {
                message[i] = substitution_table[message[i] - 'A'];
            } else {
                message[i] = tolower(substitution_table[toupper(message[i]) - 'A']);
            }
        }
    }
}
void decrypt(char message[], char substitution_table[]) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            if (isupper(message[i])) {
                message[i] = 'A' + strchr(substitution_table, message[i]) - substitution_table;
            } else {
                message[i] = tolower('A' + strchr(substitution_table, toupper(message[i])) - substitution_table);
            }
        }
    }
}

int main() {
    char message[100];
    char substitution_table[ALPHABET_SIZE + 1];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  
    printf("Enter the substitution table (26 characters in uppercase): ");
    fgets(substitution_table, sizeof(substitution_table), stdin);
    substitution_table[strcspn(substitution_table, "\n")] = '\0';  
    printf("Original message: %s\n", message);
    encrypt(message, substitution_table);
    printf("Encrypted message: %s\n", message);
    decrypt(message, substitution_table);
    printf("Decrypted message: %s\n", message);
    return 0;
}

