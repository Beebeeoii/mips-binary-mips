#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction-code-translator.h"
#include "radix-translator.h"
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
#define INPUT_MIPS 0
#define INPUT_BINARY 1
#define INPUT_HEX 2

int getInputType(char*);
void binaryToMIPS(char*, char*);

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
    printf("Your Input: %s\n", userInput);
    int inputType = getInputType(userInput);
    printf("Input Type: %s\n", inputType == INPUT_MIPS ? "MIPS" : inputType == INPUT_HEX ? "HEX" : "BINARY");
    printf("\n------------------------\n\n");
    printf("OUTPUT:\n\n");

    switch (inputType) {
        case INPUT_MIPS:
        // TODO
            break;
        case INPUT_BINARY:
            binaryToHex(userInput, hexRep);
            printf("HEX EQUIVALENT: %s\n", hexRep);
            binaryToMIPS(userInput, mipsRep);
            printf("MIPS INSTRUCTION : %s\n\n", mipsRep);
            break;
        case INPUT_HEX:
            hexToBinary(userInput, binaryRep);
            printf("BINARY EQUIVALENT: %s\n", binaryRep);
            binaryToMIPS(binaryRep, mipsRep);
            printf("MIPS INSTRUCTION : %s\n\n", mipsRep);
            break;
    }

    printf("------------------------\n");
    printf("Press ENTER key to exit\n");  
    getchar();
    return 0;
}

int getInputType(char *input) {
    if (strchr(input, ' ')) {
        return INPUT_MIPS;
    }

    return strlen(input) == HEX_LENGTH ? INPUT_HEX : INPUT_BINARY;
}

void binaryToMIPS(char *binary, char *output) {
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
                snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rd), binaryToDecimal(rt), binaryToDecimal(shamt));
                break;
            }

            snprintf(output, MAX_LENGTH, "%s $%d, $%d, $%d", instruction, binaryToDecimal(rd), binaryToDecimal(rs), binaryToDecimal(rt));
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
                snprintf(output, MAX_LENGTH, "%s $%d, %d($%d)", instruction, binaryToDecimal(rt), binaryToTwoComplement(immediate), binaryToDecimal(rs));
                break;
            }

            if (strcmp(instruction, "beq") == 0 || strcmp(instruction, "bne") == 0) {
                snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rs), binaryToDecimal(rt), binaryToTwoComplement(immediate));
                break;
            }

            snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rt), binaryToDecimal(rs), binaryToTwoComplement(immediate));
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

            snprintf(output, MAX_LENGTH, "%s 0x%s", instruction, addressHex);
            break;
        }
    }
}