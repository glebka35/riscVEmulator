//
// Created by Глеб Уваркин on 2019-11-24.
//

#ifndef RISCVCLIONPROJECT_EMULATOR_H
#define RISCVCLIONPROJECT_EMULATOR_H

#include <stdlib.h>
#include "Instructions.h"
#include "Memory.h"


class Emulator {
public:
    Emulator();
    ~Emulator();
    // General purpose registers; x[0] = 0
    int x[32];

    // Pointer to memory
    Memory memory;

    //Stack pointer
    uint32_t *stackPointer;

    void execute(rTypeInstruction *rType);
    void execute(iTypeInstruction *iType);
    void execute(uTypeInstruction *uType);
    void printState();

};

#endif //RISCVCLIONPROJECT_EMULATOR_H
