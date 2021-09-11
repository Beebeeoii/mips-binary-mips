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
void binaryToHex(char*, char*);
void decimalToBinary(int, char*);
int binaryToDecimal(char*);
int binaryToTwoComplement(char*);
void binaryToMIPS(char*, char*);
char getInstructionType(char*);
void getInstruction(char*, char*, char*);
int binaryStringToInt(char);
char hexVal(int);

int main() {
    char userInput[MAX_LENGTH], binaryRep[BINARY_LENGTH + 1], hexRep[HEX_LENGTH + 1], mipsRep[MAX_LENGTH];
    
    printf("\n------------------------\n");
    printf("MIPS-BINARY-MIPS\n\n");
    printf("With me, I can help you to:\n");
    printf("1) Convert BINARY machine code to equivalent MIPS instruction\n");
    printf("2) Convert HEX machine code to equivalent MIPS instruction.\n");
    printf("3) Convert MIPS instruction to equivalent BINARY machine code.\n");
    printf("4) Convert MIPS instruction to equivalent HEX machine code.\n");
    printf("------------------------\n\n");
    printf("Input BINARY/HEX/MIPS: ");
    fgets(userInput, MAX_LENGTH, stdin);
    if (userInput[strlen(userInput) - 1] == '\n') {
        userInput[strlen(userInput) - 1] = '\0';
    }
    printf("\n------------------------\n\n");
    printf("You have inputted: %s\n", userInput);
    printf("Input Type: %s\n", getInputType(userInput));
    printf("\n------------------------\n\n");
    printf("OUTPUT:\n\n");

    binaryToMIPS(userInput, mipsRep);

    printf("\n\n------------------------\n");

    return 0;
}

char* getInputType(char *input) {
    if (strchr(input, ' ')) {
        return "MIPS";
    }

    return strlen(input) == HEX_LENGTH ? "HEX" : "BINARY";
}

void binaryToHex(char *binary, char *output) {
    int value = 0;
    int nBits = strlen(binary);
    int totalHexLengthRequired = (nBits / 4) + (nBits % 4 == 0 ? 0 : 1);
    int counter = 1;
    for (int i = nBits - 1; i >= 0; i --) {
        value += (binaryStringToInt(*(binary + i))) * (int) pow(2, (nBits - 1 - i) % 4);

        if ((nBits - 1 - i) % 4 == 3 || i == 0) {
            output[totalHexLengthRequired - counter] = hexVal(value);
            value = 0;
            counter ++;
        }
    }

    output[totalHexLengthRequired] = '\0';
}

void decimalToBinary(int decimal, char *binaryRep) {
	int value = 0;
    int nBits = sizeof(binaryRep) / sizeof(binaryRep[0]);
    int counter = 1;
	
    while (decimal != 0) {
        binaryRep[nBits - counter] = decimal % 2 + '0';
        decimal /= 2;
        counter ++;
    }
}

int binaryToDecimal(char *binaryRep) {
	int value = 0;
    int nBits = strlen(binaryRep);
    for (int i = 0; i < nBits; i ++) {
        value += (binaryStringToInt(*(binaryRep + i))) * (int) pow(2, nBits - i - 1);
    }
    return value;
}

int binaryToTwoComplement(char *binaryRep) {
	int value = 0;
    int nBits = strlen(binaryRep);
    for (int i = 0; i < nBits; i ++) {
        if (i == 0 && binaryStringToInt(*(binaryRep + i)) == 1) {
            value -= binaryStringToInt(*(binaryRep + i)) * (int) pow(2, nBits - i - 1);
            continue;
        }
        value += (binaryStringToInt(*(binaryRep + i))) * (int) pow(2, nBits - i - 1);
    }
    return value;
}

void binaryToMIPS(char *binary, char *mips) {
    char opCode[OPCODE_LENGTH + 1];
    for (int i = 0; i < OPCODE_LENGTH; i ++) {
        opCode[i] = binary[i];
    }
    opCode[OPCODE_LENGTH] = '\0';

    char instructionType = getInstructionType(opCode);
    int offset = OPCODE_LENGTH;

    switch (instructionType) {
        case 'R': {
            char rs[RS_LENGTH + 1], rt[RT_LENGTH + 1], rd[RD_LENGTH + 1], shamt[SHAMT_LENGTH + 1], fnCode[FN_LENGTH + 1], instruction[10];

            for (int i = 0; i < RS_LENGTH; i ++) {
                rs[i] = binary[offset + i];
            }
            rs[RS_LENGTH] = '\0';
            offset += RS_LENGTH;

            for (int i = 0; i < RT_LENGTH; i ++) {
                rt[i] = binary[offset + i];
            }
            rt[RT_LENGTH] = '\0';
            offset += RT_LENGTH;

            for (int i = 0; i < RD_LENGTH; i ++) {
                rd[i] = binary[offset + i];
            }
            rd[RD_LENGTH] = '\0';
            offset += RD_LENGTH;

            for (int i = 0; i < SHAMT_LENGTH; i ++) {
                shamt[i] = binary[offset + i];
            }
            shamt[SHAMT_LENGTH] = '\0';
            offset += SHAMT_LENGTH;

            for (int i = 0; i < FN_LENGTH; i ++) {
                fnCode[i] = binary[offset + i];
            }
            fnCode[FN_LENGTH] = '\0';

            getInstruction(opCode, fnCode, instruction);

            if (strcmp(instruction, "sll") == 0 || strcmp(instruction, "srl") == 0) {
                printf("%s $%d, $%d, %d", instruction, binaryToDecimal(rd), binaryToDecimal(rt), binaryToDecimal(shamt));
                break;
            }

            printf("%s $%d, $%d, $%d", instruction, binaryToDecimal(rd), binaryToDecimal(rs), binaryToDecimal(rt));
            break;
        }
        case 'I': {
            char rs[RS_LENGTH + 1], rt[RT_LENGTH + 1], immediate[IMMEDIATE_LENGTH + 1], instruction[10];
            for (int i = 0; i < RS_LENGTH; i ++) {
                rs[i] = binary[offset + i];
            }
            rs[RS_LENGTH] = '\0';
            offset += RS_LENGTH;

            for (int i = 0; i < RT_LENGTH; i ++) {
                rt[i] = binary[offset + i];
            }
            rt[RT_LENGTH] = '\0';
            offset += RT_LENGTH;

            for (int i = 0; i < IMMEDIATE_LENGTH; i ++) {
                immediate[i] = binary[offset + i];
            }
            immediate[IMMEDIATE_LENGTH] = '\0';

            getInstruction(opCode, NULL, instruction);

            if (strcmp(instruction, "lw") == 0 || strcmp(instruction, "sw") == 0) {
                printf("%s $%d, %d($%d)", instruction, binaryToDecimal(rt), binaryToTwoComplement(immediate), binaryToDecimal(rs));
                break;
            }

            if (strcmp(instruction, "beq") == 0 || strcmp(instruction, "bne") == 0) {
                printf("%s $%d, $%d, %d", instruction, binaryToDecimal(rs), binaryToDecimal(rt), binaryToTwoComplement(immediate));
                break;
            }

            printf("%s $%d, $%d, %d", instruction, binaryToDecimal(rt), binaryToDecimal(rs), binaryToTwoComplement(immediate));
            break;
        }
        case 'J': {
            char address[ADDRESS_LENGTH + 1], addressHex[9], instruction[10];
            for (int i = 0; i < ADDRESS_LENGTH; i ++) {
                address[i] = binary[offset + i];
            }
            address[ADDRESS_LENGTH] = '\0';

            getInstruction(opCode, NULL, instruction);
            binaryToHex(address, addressHex);

            printf("%s 0x%s", instruction, addressHex);
            break;
        }
    }
}

char getInstructionType(char *opCode) {
    if (strcmp(opCode, "000000") == 0) {
        return 'R';
    }

    if (strcmp(opCode, "000010") == 0 || strcmp(opCode, "000011") == 0) {
        return 'J';
    }
    
    return 'I';
}

void getInstruction(char *opCode, char *fnCode, char *output) {
    if (strcmp(opCode, "001000") == 0) {
        strcpy(output, "addi");
    } else if (strcmp(opCode, "001001") == 0) {
        strcpy(output, "addiu");
    } else if (strcmp(opCode, "001100") == 0) {
        strcpy(output, "andi");
    } else if (strcmp(opCode, "000100") == 0) {
        strcpy(output, "beq");
    } else if (strcmp(opCode, "000101") == 0) {
        strcpy(output, "bne");
    } else if (strcmp(opCode, "000010") == 0) {
        strcpy(output, "j");
    } else if (strcmp(opCode, "000011") == 0) {
        strcpy(output, "jal");
    } else if (strcmp(opCode, "100100") == 0) {
        strcpy(output, "lbu");
    } else if (strcmp(opCode, "100101") == 0) {
        strcpy(output, "lhu");
    } else if (strcmp(opCode, "110000") == 0) {
        strcpy(output, "ll");
    } else if (strcmp(opCode, "001111") == 0) {
        strcpy(output, "lui");
    } else if (strcmp(opCode, "100011") == 0) {
        strcpy(output, "lw");
    } else if (strcmp(opCode, "001101") == 0) {
        strcpy(output, "ori");
    } else if (strcmp(opCode, "001010") == 0) {
        strcpy(output, "slti");
    } else if (strcmp(opCode, "001011") == 0) {
        strcpy(output, "sltiu");
    } else if (strcmp(opCode, "101000") == 0) {
        strcpy(output, "sb");
    } else if (strcmp(opCode, "111000") == 0) {
        strcpy(output, "sc");
    } else if (strcmp(opCode, "101001") == 0) {
        strcpy(output, "sh");
    } else if (strcmp(opCode, "101011") == 0) {
        strcpy(output, "sw");
    }

    if (strcmp(opCode, "000000") == 0) {
        if (strcmp(fnCode, "100000") == 0) {
            strcpy(output, "add");
        } else if (strcmp(fnCode, "100001") == 0) {
            strcpy(output, "addu");
        } else if (strcmp(fnCode, "100100") == 0) {
            strcpy(output, "and");
        } else if (strcmp(fnCode, "001000") == 0) {
            strcpy(output, "jr");
        } else if (strcmp(fnCode, "100111") == 0) {
            strcpy(output, "nor");
        } else if (strcmp(fnCode, "100101") == 0) {
            strcpy(output, "or");
        } else if (strcmp(fnCode, "101010") == 0) {
            strcpy(output, "slt");
        } else if (strcmp(fnCode, "101011") == 0) {
            strcpy(output, "sltu");
        } else if (strcmp(fnCode, "000000") == 0) {
            strcpy(output, "sll");
        } else if (strcmp(fnCode, "000010") == 0) {
            strcpy(output, "srl");
        } else if (strcmp(fnCode, "100010") == 0) {
            strcpy(output, "sub");
        } else if (strcmp(fnCode, "100011") == 0) {
            strcpy(output, "subu");
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