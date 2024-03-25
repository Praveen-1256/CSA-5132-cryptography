#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to print a matrix
void printMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to allocate memory for a matrix
int **allocateMatrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to convert a character to its corresponding integer value (A->0, B->1, ..., Z->25)
int charToInt(char c) {
    return toupper(c) - 'A';
}

// Function to convert an integer to its corresponding character value (0->A, 1->B, ..., 25->Z)
char intToChar(int n) {
    return 'A' + n;
}

// Function to perform matrix multiplication
int **multiplyMatrices(int **matrix1, int **matrix2, int size) {
    int **result = allocateMatrix(size);
    int sum;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum = 0;
            for (int k = 0; k < size; k++) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum % 26; // Modulo 26 operation for Hill cipher
        }
    }

    return result;
}

// Function to encrypt the message using Hill cipher
void encrypt(char message[], int **keyMatrix, int keySize) {
    int messageLen = strlen(message);
    int matrixSize = keySize;
    int rows = (messageLen + matrixSize - 1) / matrixSize;
    int **messageMatrix = allocateMatrix(rows);
    int **encryptedMatrix;

    // Convert the message into a matrix
    int index = 0;
    for (int i = 0; i < rows; i++) {
        messageMatrix[i] = (int *)malloc(matrixSize * sizeof(int));
        for (int j = 0; j < matrixSize; j++) {
            if (index < messageLen) {
                messageMatrix[i][j] = charToInt(message[index]);
            } else {
                messageMatrix[i][j] = charToInt('X'); // Pad with 'X' if necessary
            }
            index++;
        }
    }

    // Perform encryption
    encryptedMatrix = multiplyMatrices(messageMatrix, keyMatrix, matrixSize);

    // Convert the encrypted matrix back to characters
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < matrixSize; j++) {
            message[index] = intToChar(encryptedMatrix[i][j]);
            index++;
        }
    }

    // Free memory
    freeMatrix(messageMatrix, rows);
    freeMatrix(encryptedMatrix, rows);
}

// Function to calculate the inverse of a 2x2 matrix (for Hill cipher with keySize=2)
int **calculateInverse2x2(int **keyMatrix) {
    int determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    int inverseDeterminant;
    int **inverseMatrix = allocateMatrix(2);

    // Calculate determinant inverse modulo 26
    for (int i = 1; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            inverseDeterminant = i;
            break;
        }
    }

    // Calculate adjugate matrix
    inverseMatrix[0][0] = keyMatrix[1][1];
    inverseMatrix[1][1] = keyMatrix[0][0];
    inverseMatrix[0][1] = -keyMatrix[0][1];
    inverseMatrix[1][0] = -keyMatrix[1][0];

    // Apply inverse determinant modulo 26 to the adjugate matrix
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverseMatrix[i][j] = (inverseMatrix[i][j] * inverseDeterminant) % 26;
            if (inverseMatrix[i][j] < 0) {
                inverseMatrix[i][j] += 26; // Ensure the result is positive
            }
        }
    }

    return inverseMatrix;
}

// Function to decrypt the message using Hill cipher
void decrypt(char message[], int **keyMatrix, int keySize) {
    int determinant;
    int **inverseMatrix;
    int **decryptionMatrix;

    // Calculate determinant of the key matrix
    if (keySize == 2) {
        determinant = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
        if (determinant == 0) {
            printf("Cannot decrypt with a singular key matrix.\n");
            return;
        }
    } else {
        printf("Decryption is only supported for 2x2 key matrices.\n");
        return;
    }

    // Calculate the inverse of the key matrix
    inverseMatrix = calculateInverse2x2(keyMatrix);

    // Perform decryption
    decryptionMatrix = multiplyMatrices(inverseMatrix, keyMatrix, keySize);

    // Perform modulo 26 operation
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            decryptionMatrix[i][j] = decryptionMatrix[i][j] % 26;
            if (decryptionMatrix[i][j] < 0) {
                decryptionMatrix[i][j] += 26; // Ensure the result is positive
            }
        }
    }

    // Encrypt the message using the decryption matrix
    encrypt(message, decryptionMatrix,

