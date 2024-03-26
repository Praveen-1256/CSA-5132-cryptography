#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt(char plaintext[], int key[], char ciphertext[]) {
    int len = strlen(plaintext);
    int key_len = strlen(plaintext); 
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % key_len];
            
            if (isupper(plaintext[i]))
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            else
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0'; 
}

void decrypt(char ciphertext[], int key[], char decrypted[]) {
    int len = strlen(ciphertext);
    int key_len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % key_len];

            if (isupper(ciphertext[i]))
                decrypted[i] = 'A' + (ciphertext[i] - 'A' - shift + 26) % 26;
            else
                decrypted[i] = 'a' + (ciphertext[i] - 'a' - shift + 26) % 26;
        } else {
            decrypted[i] = ciphertext[i];
        }
    }

    decrypted[i] = '\0'; 
}

int main() {
    char plaintext[100]; 
    int key[100]; 
    char ciphertext[100];
    char decrypted[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key (space-separated integers): ");
    for (int i = 0; i < strlen(plaintext); i++) {
        scanf("%d", &key[i]);
    }

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted);
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}

