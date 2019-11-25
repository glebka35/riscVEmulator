//
// Created by Глеб Уваркин on 2019-11-24.
//

#ifndef RISCVCLIONPROJECT_EMULATOR_H
#define RISCVCLIONPROJECT_EMULATOR_H

#include <stdlib.h>
#include "Instructions.h"


class Emulator {
public:
    Emulator();
    ~Emulator();
    // General purpose registers; x[0] = 0
    int x[32];

    // Pointer to memory
    int *memory;

    //Stack pointer
    int *stackPointer;

    void execute(rTypeInstruction *rType);
    void execute(iTypeInstruction *iType);
    void printState();

};

#endif //RISCVCLIONPROJECT_EMULATOR_H
