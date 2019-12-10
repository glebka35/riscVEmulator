#include <iostream>

#include "Emulator.h"
#include "Instructions.h"



int main() {
    // Чтение elf файла -> инструкция (32 бита)

    Emulator riscV;

//    std::cout << "Initial state" << std::endl;
//    riscV.printState();

    riscV.loadProgramToMemory("ptloadQueen.txt");
    riscV.mainExecuteCommands();

   // riscV.memory.printMemory();
    std::cout << "Final state:" << std::endl;
    riscV.printState();
    return 0;
}