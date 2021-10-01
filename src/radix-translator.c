#include "radix-translator.h"
#include <string.h>
#include <math.h>

void binaryToHex(char *binary, char *output) {
    int value = 0;
    int nBits = strlen(binary);
    int totalHexLengthRequired = (nBits / 4) + (nBits % 4 == 0 ? 0 : 1);
    int counter = 1;
    for (int i = nBits - 1; i >= 0; i --) {
        value += (binaryStringToInt(*(binary + i))) * (int) pow(BINARY_BASE_WEIGHT, (nBits - 1 - i) % 4);

        if ((nBits - 1 - i) % 4 == 3 || i == 0) {
            output[totalHexLengthRequired - counter] = valToHex(value);
            value = 0;
            counter ++;
        }
    }

    output[totalHexLengthRequired] = '\0';
}

int binaryToDecimal(char *binaryRep) {
	int value = 0;
    int nBits = strlen(binaryRep);
    for (int i = 0; i < nBits; i ++) {
        value += (binaryStringToInt(*(binaryRep + i))) * (int) pow(BINARY_BASE_WEIGHT, nBits - i - 1);
    }
    return value;
}

int binaryToTwoComplement(char *binaryRep) {
	int value = 0;
    int nBits = strlen(binaryRep);
    for (int i = 0; i < nBits; i ++) {
        if (i == 0 && binaryStringToInt(*(binaryRep + i)) == 1) {
            value -= binaryStringToInt(*(binaryRep + i)) * (int) pow(BINARY_BASE_WEIGHT, nBits - i - 1);
            continue;
        }
        value += (binaryStringToInt(*(binaryRep + i))) * (int) pow(BINARY_BASE_WEIGHT, nBits - i - 1);
    }
    return value;
}

void decimalToBinary(int decimal, char *output) {
    int nBits = strlen(output);
    int counter = 1;
	
    while (decimal != 0 || counter <= nBits) {
        output[nBits - counter] = decimal % 2 + '0';
        decimal /= 2;
        counter ++;
    }
}

void hexToBinary(char *hex, char *output) {
    for (int i = 0; i < strlen(hex); i ++) {
        char binaryPartition[5] = {'0', '0', '0', '0', '\0'};
        decimalToBinary(hexToVal(hex[strlen(hex) - 1 - i]), binaryPartition);

        for (int j = 0; j < strlen(binaryPartition); j ++) {
            output[BINARY_LENGTH - (strlen(binaryPartition) * (i + 1)) + j] = binaryPartition[j];
        }
    }
    output[BINARY_LENGTH] = '\0';
}

int binaryStringToInt(char binaryChar) {
    return binaryChar == '1' ? 1 : 0;
}

char valToHex(int value) {
    switch (value) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return 0;
    }
}

int hexToVal(char hex) {
    switch (hex) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return 0;
    }
}