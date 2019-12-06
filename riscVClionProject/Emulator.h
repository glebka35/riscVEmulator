//
// Created by Глеб Уваркин on 2019-11-24.
//

#ifndef RISCVCLIONPROJECT_EMULATOR_H
#define RISCVCLIONPROJECT_EMULATOR_H

#include <stdlib.h>
#include <fstream>
#include "Instructions.h"
#include "Memory.h"


class Emulator {
public:
    Emulator();
    ~Emulator();

    // General purpose registers; x[0] = 0
    uint32_t x[32];

    // Main memory
    Memory memory;

    //Program Counter
    uint32_t pc;

    void loadProgramToMemory(std::string fileName);
    void mainExecuteCommands();

    void execute(rTypeInstruction rType);
    void execute(iTypeInstruction iType);
    void execute(uTypeInstruction uType);
    void execute(jTypeInstruction jType);
    void execute(iLoadTypeInstruction iLoadType);
    void execute(bTypeInstruction bType);
    void execute(sTypeInstruction sType);

    void printState();
};

#endif //RISCVCLIONPROJECT_EMULATOR_H
