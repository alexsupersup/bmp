#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

char* reverse(const char* text) {
    int len = strlen(text);
    char *rev = malloc(len * sizeof(char));

    if(rev == NULL) {
        return NULL;
    }

    for(int i = 0; i <= len; i++) {
        rev[i] = text[len - i - 1];
        if(rev[i] >= 97 && rev[i] <= 122) {
            rev[i] -= 32;
        }
        // printf("%c\n", rev[i]);
    }

    return rev;
}

char* vigenere_encrypt(const char* key, const char* text) {
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // char ints[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    
    int lenText = strlen(text);
    char *encr = malloc(lenText * sizeof(char));
    // char temp[lenText];
    char *temp = malloc(lenText * sizeof(char));
    // printf("len: %d\n", lenText);

    // "CoMPuTeR" "Hello world!" "JSXAI PSINR!"
    //    9            13
    for(int i = 0; i < lenText;) {
        for(int j = 0; j < strlen(key); i++, j++) {
            if(text[i] <= 64 || (text[i] >= 91 && text[i] <= 96) || (text[i] >= 123 && text[i] <= 127)) {
                temp[i] = ' ';
                j--;
            } else {
                temp[i] = key[j];
                if(text[i] == ' ') {
                    temp[i] = ' ';
                    j--;
                } else if(temp[i] >= 97 && temp[i] <= 122) {
                    temp[i] -= 32;
                } else if(i >= lenText) {
                    break;
                }
            }
        }
        if(i >= lenText) {
            break;
        }
    }
    temp[lenText] = '\0';

    // printf("%s\n", text);
    // printf("%s\n", temp);


    int posEncrEl;
    for(int i = 0; i < lenText; i++) {

        char tmpText = text[i];
        char tmpTemp = temp[i];
        if(tmpText >= 97 && tmpText <= 122) {
            tmpText -= 32;
        }
        
        int enterPosText = tmpText - 65;
        int enterPosTemp = tmpTemp - 65;
        int sum = enterPosText + enterPosTemp;

        if(sum < 26 && sum >= 0) {
            posEncrEl = sum;
        } else if(sum > 26) {
            posEncrEl = sum % 26;
        } else {
            posEncrEl = 26 - sum;
        }

        if((text[i] >= 97 && text[i] <= 122) || (text[i] >= 65 && text[i] <= 90)) {
            encr[i] = alphabet[posEncrEl];
        } else if(text[i] == ' ') {
            encr[i] = ' ';
        } else {
            encr[i] = text[i];
        }

        // printf("El1: %c, el2: %c - num1: %d, num2: %d / sum: %d\n", tmpText, tmpTemp, enterPosText, enterPosTemp, sum);

    }
    free(temp);
    return encr;
}

char* vigenere_decrypt(const char* key, const char* text) {
    
    // char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int lenText = strlen(text);
    char *decr = malloc(lenText * sizeof(char));

    char *temp = malloc(lenText * sizeof(char));
    for(int i = 0; i < lenText;) {
        for(int j = 0; j < strlen(key); i++, j++) {
            if(text[i] <= 64 || (text[i] >= 91 && text[i] <= 96) || (text[i] >= 123 && text[i] <= 127)) {
                temp[i] = ' ';
                j--;
            } else {
                temp[i] = key[j];
                if(text[i] == ' ') {
                    temp[i] = ' ';
                    j--;
                } else if(temp[i] >= 97 && temp[i] <= 122) {
                    temp[i] -= 32;
                } else if(i >= lenText) {
                    break;
                }
            }
        }
        if(i >= lenText) {
            break;
        }
    }
    temp[lenText] = '\0';

    int posDecrEl;
    for(int i = 0; i < lenText; i++) {
        char tmpText = text[i];
        char tmpTemp = temp[i];

        int enterPosText = tmpText - 65;
        int enterPosTemp = tmpTemp - 65;
        int diff = enterPosText - enterPosTemp;

        if(diff < 0) {
            diff += 26;
        }
        if(diff < 26) {
            posDecrEl = diff;
        }

        if((text[i] >= 97 && text[i] <= 122) || (text[i] >= 65 && text[i] <= 90)) {
            decr[i] = posDecrEl + 65;
        } else if(text[i] == ' ') {
            decr[i] = ' ';
        } else {
            decr[i] = text[i];
        }
    }

    free(temp);
    return decr;
}

unsigned char* bit_encrypt(const char* text) {

    int lentext = strlen(text);
    unsigned char *unsCh = malloc(lentext * sizeof(char));

    int bits[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    // char* temp = malloc(8 * sizeof(char));
    int temp[8];
    int first[4];
    int second[4];


    for(int i = 0; i < lentext; i++) {
        int myChar = 0;
        int tChar = (int)text[i];
        for(int j = 0; j < 8; j++) {
            temp[j] = 0;
            if(tChar >= bits[j]) {
                temp[j] = 1;
                tChar -= bits[j];
            }
            if(j < 4) {
                first[j] = temp[j];
            } else {
                second[j - 4] = temp[j];
            }
        }

        first[0] = temp[1];
        first[1] = temp[0];
        first[2] = temp[3];
        first[3] = temp[2];
    
        temp[0] = first[0];
        temp[1] = first[1];
        temp[2] = first[2];
        temp[3] = first[3];
        
        for(int j = 0; j < 4; j++) {
            // printf("first: %d\n", first[j]);
            if(temp[j] != second[j]) {
                temp[j + 4] = 1;
            } else {
                temp[j + 4] = 0;
            }
            
        }

        for(int j = 0; j < 8; j++) {
            // printf("temp: %d\n", temp[j]);
            if(temp[j] == 1) {
                myChar += bits[j];
            }
        }
        
        unsCh[i] = (unsigned char)myChar;
    }

    return unsCh;
}

char* bit_decrypt(const unsigned char* text) {
    int lenText = 0;
    while(text[lenText] != '\0') {
        lenText++;
    }
    printf("Len: %d\n", lenText);

    char *returnedCh = malloc(lenText * sizeof(char));

    int bits[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    int temp[8];
    int returnedInt = 0;
    
    // printf("\n");

    for(int i = 0; i < lenText; i++) {
        int intTempChar = (int)text[i];
        // printf("%d - %d: ", i, intTempChar);

        for(int j = 0; j < 8; j++) {
            temp[j] = 0;
            if(intTempChar >= bits[j]) {
                intTempChar -= bits[j];
                temp[j] = 1;
            }
            // printf("%d ", temp[j]);
        }
        // printf("\n");

        for(int j = 0; j < 4; j++) {
            if(temp[j] == temp[j + 4]) {
                temp[j + 4] = 0;
            } else {
                temp[j + 4] = 1;
            }
        }
        
        // for(int j = 0; j < 8; j++) {
        //     printf("%d ", temp[j]);
        // }
        // printf("\n");

        int blabla = temp[0];
        temp[0] = temp[1];
        temp[1] = blabla;
        blabla = temp[2];
        temp[2] = temp[3];
        temp[3] = blabla;

        for(int j = 0; j < 8; j++) {
            if(temp[j] == 1) {
                returnedInt += bits[j];
            }
        }
        returnedCh[i] = (char)returnedInt;
        returnedInt = 0;
    }

    return returnedCh;
}
