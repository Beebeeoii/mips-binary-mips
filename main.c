#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_LENGTH 64
#define BINARY_LENGTH 32
#define HEX_LENGTH 8
#define OPCODE_LENGTH 6
#define RS_LENGTH 5
#define RT_LENGTH 5
#define RD_LENGTH 5
#define SHAMT_LENGTH 5
#define FN_LENGTH 6
#define IMMEDIATE_LENGTH 16
#define ADDRESS_LENGTH 26

char* getInputType(char*);
int binaryStringToInt(char);
void binaryToHex(char*, char*);
void binaryToMIPS(char*, char*);
char* getInstruction(char*, char*);
char hexVal(int);

int main() {
    char userInput[MAX_LENGTH], binaryRep[BINARY_LENGTH + 1], hexRep[HEX_LENGTH + 1], mipsRep[MAX_LENGTH];
    
    printf("------------------------\n");
    printf("Input a BINARY/HEX to convert to equivalent MIPS instruction.\n");
    printf("Input a MIPS instruction to convert to equivalent BINARY/HEX encoding.\n");
    printf("------------------------\n");
    printf("Your input: ");
    fgets(userInput, MAX_LENGTH, stdin);
    if (userInput[strlen(userInput) - 1] == '\n') {
        userInput[strlen(userInput) - 1] = '\0';
    }
    printf("------------------------\n");
    printf("You have inputted: %s\n", userInput);


    printf("Input Type: %s\n", getInputType(userInput));
    binaryToMIPS(userInput, mipsRep);

    // 00000001010010110100100000100000 -> add $1, $2, $3
    return 0;
}

char* getInputType(char *input) {
    if (strchr(input, ' ')) {
        return "MIPS";
    }

    return strlen(input) == HEX_LENGTH ? "HEX" : "BINARY";
}

void binaryToHex(char *binary, char *hexRep) {
    int value = 0;
    for (int i = 0; i < BINARY_LENGTH; i ++) {
        value += (binaryStringToInt(*(binary + i))) * (int) pow(2, 3 - (i % 4));

        if ((i != 0 && i % 4 == 3)) {
            hexRep[(i / 4)] = hexVal(value);
            value = 0;
        }
    }
    hexRep[8] = '\0';
}

void binaryToMIPS(char *binary, char *mips) {
    char opCode[OPCODE_LENGTH + 1];

    char immediate[OPCODE_LENGTH];
    char address[OPCODE_LENGTH];
    
    for (int i = 0; i < 6; i ++) {
        opCode[i] = binary[i];
    }
    opCode[OPCODE_LENGTH] = '\0';

    if (strcmp(opCode, "000000") == 0) {
        char rs[RS_LENGTH];
        char rt[RT_LENGTH];
        char rd[RD_LENGTH];
        char shamt[SHAMT_LENGTH];
        char fnCode[FN_LENGTH + 1];

        for (int j = BINARY_LENGTH - 6; j < BINARY_LENGTH; j ++) {
            fnCode[j - BINARY_LENGTH + 6] = binary[j];
        }
        fnCode[FN_LENGTH] = '\0';
    }

    //TODO
}

char* getInstruction(char *opCode, char *fnCode) {
    if (strcmp(opCode, "001000") == 0) {
        return "addi";
    } else if (strcmp(opCode, "001001") == 0) {
        return "addiu";
    } else if (strcmp(opCode, "001100") == 0) {
        return "andi";
    } else if (strcmp(opCode, "000100") == 0) {
        return "beq";
    } else if (strcmp(opCode, "000101") == 0) {
        return "bne";
    } else if (strcmp(opCode, "000010") == 0) {
        return "j";
    } else if (strcmp(opCode, "000011") == 0) {
        return "jal";
    } else if (strcmp(opCode, "100100") == 0) {
        return "lbu";
    } else if (strcmp(opCode, "100101") == 0) {
        return "lhu";
    } else if (strcmp(opCode, "110000") == 0) {
        return "ll";
    } else if (strcmp(opCode, "001111") == 0) {
        return "lui";
    } else if (strcmp(opCode, "100011") == 0) {
        return "lw";
    } else if (strcmp(opCode, "001101") == 0) {
        return "ori";
    } else if (strcmp(opCode, "001010") == 0) {
        return "slti";
    } else if (strcmp(opCode, "001011") == 0) {
        return "sltiu";
    } else if (strcmp(opCode, "101000") == 0) {
        return "sb";
    } else if (strcmp(opCode, "111000") == 0) {
        return "sc";
    } else if (strcmp(opCode, "101001") == 0) {
        return "sh";
    } else if (strcmp(opCode, "101011") == 0) {
        return "sw";
    }

    if (strcmp(opCode, "000000") == 0) {
        if (strcmp(fnCode, "100000") == 0) {
            return "add";
        } else if (strcmp(fnCode, "100001") == 0) {
            return "addu";
        } else if (strcmp(fnCode, "100100") == 0) {
            return "and";
        } else if (strcmp(fnCode, "001000") == 0) {
            return "jr";
        } else if (strcmp(fnCode, "100111") == 0) {
            return "nor";
        } else if (strcmp(fnCode, "100101") == 0) {
            return "or";
        } else if (strcmp(fnCode, "101010") == 0) {
            return "slt";
        } else if (strcmp(fnCode, "101011") == 0) {
            return "sltu";
        } else if (strcmp(fnCode, "000000") == 0) {
            return "sll";
        } else if (strcmp(fnCode, "000010") == 0) {
            return "srl";
        } else if (strcmp(fnCode, "100010") == 0) {
            return "sub";
        } else if (strcmp(fnCode, "100011") == 0) {
            return "subu";
        }
    }
}

int binaryStringToInt(char binaryChar) {
    return binaryChar == '1' ? 1 : 0;
}

char hexVal(int value) {
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