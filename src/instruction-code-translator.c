#include "instruction-code-translator.h"
#include <string.h>

char getInstructionType(char *opCode) {
    if (!strcmp(opCode, "000000")) {
        return 'R';
    }

    if (!strcmp(opCode, "000010") || !strcmp(opCode, "000011")) {
        return 'J';
    }
    
    return 'I';
}

void getOpCode(char *instruction, char *output) {
    char *rTypeInstructions[] = {"add", "addu", "and", "jr", "nor", "or", "slt", "sltu", "sll", "srl", "sub", "subu"};
    int len = sizeof(rTypeInstructions)/sizeof(rTypeInstructions[0]);

    for (int i = 0; i < len; ++i) {
        if (!strcmp(rTypeInstructions[i], instruction)) {
            strcpy(output, "000000");
        }
    }

    if (!strcmp(instruction, "addi")) {
        strcpy(output, "001000");
    } else if (!strcmp(instruction, "addiu")) {
        strcpy(output, "001001");
    } else if (!strcmp(instruction, "andi")) {
        strcpy(output, "001100");
    } else if (!strcmp(instruction, "beq")) {
        strcpy(output, "000100");
    } else if (!strcmp(instruction, "bne")) {
        strcpy(output, "000101");
    } else if (!strcmp(instruction, "j")) {
        strcpy(output, "000010");
    } else if (!strcmp(instruction, "jal")) {
        strcpy(output, "000011");
    } else if (!strcmp(instruction, "lbu")) {
        strcpy(output, "100100");
    } else if (!strcmp(instruction, "lhu")) {
        strcpy(output, "100101");
    } else if (!strcmp(instruction, "ll")) {
        strcpy(output, "110000");
    } else if (!strcmp(instruction, "lui")) {
        strcpy(output, "001111");
    } else if (!strcmp(instruction, "lw")) {
        strcpy(output, "100011");
    } else if (!strcmp(instruction, "ori")) {
        strcpy(output, "001101");
    } else if (!strcmp(instruction, "slti")) {
        strcpy(output, "001010");
    } else if (!strcmp(instruction, "sltiu")) {
        strcpy(output, "001011");
    } else if (!strcmp(instruction, "sb")) {
        strcpy(output, "101000");
    } else if (!strcmp(instruction, "sc")) {
        strcpy(output, "111000");
    } else if (!strcmp(instruction, "sh")) {
        strcpy(output, "101001");
    } else if (!strcmp(instruction, "sw")) {
        strcpy(output, "101011");
    }
}

void getFnCode(char *instruction, char *output) {
    if (!strcmp(instruction, "add")) {
        strcpy(output, "100000");
    } else if (!strcmp(instruction, "addu")) {
        strcpy(output, "100001");
    } else if (!strcmp(instruction, "and")) {
        strcpy(output, "100100");
    } else if (!strcmp(instruction, "jr")) {
        strcpy(output, "001000");
    } else if (!strcmp(instruction, "nor")) {
        strcpy(output, "100111");
    } else if (!strcmp(instruction, "or")) {
        strcpy(output, "100101");
    } else if (!strcmp(instruction, "slt")) {
        strcpy(output, "101010");
    } else if (!strcmp(instruction, "sltu")) {
        strcpy(output, "101011");
    } else if (!strcmp(instruction, "sll")) {
        strcpy(output, "000000");
    } else if (!strcmp(instruction, "srl")) {
        strcpy(output, "000010");
    } else if (!strcmp(instruction, "sub")) {
        strcpy(output, "100010");
    } else if (!strcmp(instruction, "subu")) {
        strcpy(output, "100011");
    }
}

void getInstruction(char *opCode, char *fnCode, char *output) {
    if (!strcmp(opCode, "001000")) {
        strcpy(output, "addi");
    } else if (!strcmp(opCode, "001001")) {
        strcpy(output, "addiu");
    } else if (!strcmp(opCode, "001100")) {
        strcpy(output, "andi");
    } else if (!strcmp(opCode, "000100")) {
        strcpy(output, "beq");
    } else if (!strcmp(opCode, "000101")) {
        strcpy(output, "bne");
    } else if (!strcmp(opCode, "000010")) {
        strcpy(output, "j");
    } else if (!strcmp(opCode, "000011")) {
        strcpy(output, "jal");
    } else if (!strcmp(opCode, "100100")) {
        strcpy(output, "lbu");
    } else if (!strcmp(opCode, "100101")) {
        strcpy(output, "lhu");
    } else if (!strcmp(opCode, "110000")) {
        strcpy(output, "ll");
    } else if (!strcmp(opCode, "001111")) {
        strcpy(output, "lui");
    } else if (!strcmp(opCode, "100011")) {
        strcpy(output, "lw");
    } else if (!strcmp(opCode, "001101")) {
        strcpy(output, "ori");
    } else if (!strcmp(opCode, "001010")) {
        strcpy(output, "slti");
    } else if (!strcmp(opCode, "001011")) {
        strcpy(output, "sltiu");
    } else if (!strcmp(opCode, "101000")) {
        strcpy(output, "sb");
    } else if (!strcmp(opCode, "111000")) {
        strcpy(output, "sc");
    } else if (!strcmp(opCode, "101001")) {
        strcpy(output, "sh");
    } else if (!strcmp(opCode, "101011")) {
        strcpy(output, "sw");
    }

    if (!strcmp(opCode, "000000")) {
        if (!strcmp(fnCode, "100000")) {
            strcpy(output, "add");
        } else if (!strcmp(fnCode, "100001")) {
            strcpy(output, "addu");
        } else if (!strcmp(fnCode, "100100")) {
            strcpy(output, "and");
        } else if (!strcmp(fnCode, "001000")) {
            strcpy(output, "jr");
        } else if (!strcmp(fnCode, "100111")) {
            strcpy(output, "nor");
        } else if (!strcmp(fnCode, "100101")) {
            strcpy(output, "or");
        } else if (!strcmp(fnCode, "101010")) {
            strcpy(output, "slt");
        } else if (!strcmp(fnCode, "101011")) {
            strcpy(output, "sltu");
        } else if (!strcmp(fnCode, "000000")) {
            strcpy(output, "sll");
        } else if (!strcmp(fnCode, "000010")) {
            strcpy(output, "srl");
        } else if (!strcmp(fnCode, "100010")) {
            strcpy(output, "sub");
        } else if (!strcmp(fnCode, "100011")) {
            strcpy(output, "subu");
        }
    }
}