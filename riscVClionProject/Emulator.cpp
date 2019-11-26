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

}

void Emulator::execute(uTypeInstruction *uType) {

}

void Emulator::printState() {
        for(int i = 0; i < 32; i ++){
            std::cout << x[i] << std::endl;
        }
    }
