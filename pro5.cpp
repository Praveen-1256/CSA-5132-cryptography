#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char message[], char key[]) {
    int messageLen = strlen(message);
    int keyLen = strlen(key);
    int i, j;
    for (i = 0, j = 0; i < messageLen; ++i, ++j) {
        if (j == keyLen)
            j = 0;
        message[i] = ((message[i] + key[j] - 2 * 'A') % 26) + 'A';
    }
}
int main() {
    char message[100];
    char key[100];
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    for (int i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i]))
            message[i] = toupper(message[i]);
    }
    for (int i = 0; key[i] != '\0'; ++i) {
        if (isalpha(key[i]))
            key[i] = toupper(key[i]);
    }

    printf("Original message: %s\n", message);

    // Encrypt the message
    encrypt(message, key);
    printf("Encrypted message: %s\n", message);

    return 0;
}

