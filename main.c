// #include <stddef.h>
// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char* argv[]) {
    // printf("Num: %d\n", argc - 1);
    // for(int i = 0; i < argc; i++) {
    //     printf("%s\n", argv[i]);
    // }
    // return 0;

    char* reversed = reverse("Hello world!");
    printf("%s\n", reversed);


    char* encryptedV;
    encryptedV = vigenere_encrypt("CoMPuTeR", reversed);
    printf("%s\n", encryptedV);


    unsigned char* encryptedBit;
    encryptedBit = bit_encrypt(encryptedV);
    for(int i = 0; i < 12; i++) {
        printf("%x ", encryptedBit[i]);
    }
    printf("\n");

    free(reversed);
    free(encryptedV);

    char* decryptedBit;
    decryptedBit = bit_decrypt(encryptedBit);

    for(int i = 0; i < 12; i++) {
        printf("%c ", decryptedBit[i]);
    }
    printf("\n");

    free(encryptedBit);

    char* decryptedV;
    decryptedV = vigenere_decrypt("CoMPuTeR", decryptedBit);
    printf("%s\n", decryptedV);

    // free(decryptedBit);
    
    char* finalText;
    finalText = reverse(decryptedV);
    printf("%s\n", finalText);

    return 0;
}
