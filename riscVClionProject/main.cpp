#include <iostream>

#include "Emulator.h"
#include "Instructions.h"


int main() {
    // Чтение elf файла -> инструкция (32 бита)

    Emulator riscV;
    riscV.loadProgramToMemory("ptload.txt");
    riscV.mainExecuteCommands();

//    riscV.memory.printMemory();
    riscV.printState();
    return 0;
}