//
// Created by Глеб Уваркин on 2019-11-24.
//

#include "Emulator.h"
#include "Instructions.h"
#include <iostream>

Emulator::Emulator() {
    std::cout << "Constructor started" << std::endl;
    // Init registers
    for (int i = 0; i < 32; i++) {
        x[i] = 0;
    }
    x[6] = 6;
    x[7] = 7;

    // Init stack
    stackPointer = (uint32_t *) malloc(16 * sizeof(int));
    for (int i = 0; i < 16; i++) {
        stackPointer[i] = 0;
    }
    std::cout << "Constructor finished" << std::endl << "----------------------" << std::endl;;
}

Emulator::~Emulator() {

    std::cout  << "----------------------" << std::endl << "Destructor started" << std::endl;
    free(stackPointer);
    std::cout << "Destructor finished" << std::endl;
}

void Emulator::execute(rTypeInstruction *rType) {
    uint8_t rs1 = rType->rs1;
    uint8_t rs2 = rType->rs2;
    uint8_t rd = rType->rd;
    switch (rType->fullInstruction & R_TYPE_MASK) {
        case add_value:
            x[rd] = x[rs1] + x[rs2];
            break;
    }
}

void Emulator::execute(iTypeInstruction *iType) {
    uint8_t rs1 = iType->rs1;
    uint32_t imm12 = iType->imm12;
    uint8_t rd = iType->rd;
    switch (iType->fullInstruction & I_TYPE_MASK) {
        case addi_value:
            if (imm12 & 0x800 == 2048){
                imm12 | 0xFFFFF000;
            }
            x[rd] = x[rs1] + x[imm12];
            break;
    }

}

void Emulator::execute(uTypeInstruction *uType) {
    uint8_t rd = uType->rd;
    uint32_t imm20 = uType->imm20;
    switch (uType->fullInstruction & U_TYPE_MASK) {
        case auipc_value:
            x[rd] = x[pc] + x[imm20];
            break;
    }
}

void Emulator::execute(jTypeInstruction *jType) {
    uint8_t rd = jType->rd;
    uint32_t imm20 = jType->imm20;
    switch (jType->fullInstruction & J_TYPE_MASK) {
        case jal_value:
            if (imm20 & 0x80000 == 524288){
                imm20 | 0xFFF00000;
            }
            x[pc] = x[pc] + x[imm20];
            break;
    }
}

void Emulator::printState() {
        for(int i = 0; i < 32; i ++){
            std::cout << x[i] << std::endl;
        }
    }
