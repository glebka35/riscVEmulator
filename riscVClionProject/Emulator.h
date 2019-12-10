//
// Created by Глеб Уваркин on 2019-11-24.
//

#ifndef RISCVCLIONPROJECT_EMULATOR_H
#define RISCVCLIONPROJECT_EMULATOR_H

#define CACHE_SIZE 10

#include <stdlib.h>
#include <fstream>
#include "Instructions.h"
#include "Memory.h"
#include "time.h"




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

    //Instruction Cache
    rTypeInstruction rTypeInstructionCache[CACHE_SIZE];
    int rTypeIndex = 0;

    iTypeInstruction iTypeInstructionCache[CACHE_SIZE];
    int iTypeIndex = 0;

    uTypeInstruction uTypeInstructionCache[CACHE_SIZE];
    int uTypeIndex = 0;

    jTypeInstruction jTypeInstructionCache[CACHE_SIZE];
    int jTypeIndex = 0;

    iLoadTypeInstruction iLoadTypeInstructionCache[CACHE_SIZE];
    int iLoadIndex = 0;

    bTypeInstruction bTypeInstructionCache[CACHE_SIZE];
    int bTypeIndex = 0;

    sTypeInstruction sTypeInstructionCache[CACHE_SIZE];
    int sTypeIndex = 0;

    void loadProgramToMemory(std::string fileName);
    void mainExecuteCommands();

    void execute(rTypeInstruction rType);
    void execute(iTypeInstruction iType);
    void execute(uTypeInstruction uType);
    void execute(jTypeInstruction jType);
    void execute(iLoadTypeInstruction iLoadType);
    void execute(bTypeInstruction bType);
    void execute(sTypeInstruction sType);

    rTypeInstruction getrTypeInstruction(uint32_t instruction);
    iTypeInstruction getiTypeInstruction(uint32_t instruction);
    uTypeInstruction getuTypeInstruction(uint32_t instruction);
    jTypeInstruction getjTypeInstruction(uint32_t instruction);
    iLoadTypeInstruction getiLoadTypeInstruction(uint32_t instruction);
    bTypeInstruction getbTypeInstruction(uint32_t instruction);
    sTypeInstruction getsTypeInstruction(uint32_t instruction);



    void printState();
};

#endif //RISCVCLIONPROJECT_EMULATOR_H
