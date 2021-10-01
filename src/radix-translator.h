#ifndef RADIX_TRANSLATOR_H
#define RADIX_TRANSLATOR_H
#define BINARY_LENGTH 32
#define BINARY_BASE_WEIGHT 2
#define HEX_LENGTH 8

void binaryToHex(char*, char*);
int binaryToDecimal(char*);
int binaryToTwoComplement(char*);

void hexToBinary(char*, char*);
void decimalToBinary(int, char*);

int binaryStringToInt(char);
char valToHex(int);
int hexToVal(char);

#endif