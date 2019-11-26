#include <iostream>
#include "Emulator.h"
#include "Instructions.h"


int main() {
    // Чтение elf файла -> инструкция (32 бита)

    Emulator riscV;
    uint32_t myInstruction = 0x007302B3;
    switch(myInstruction & 0x7F){
        case R_TYPE_OPCODE:
            riscV.execute(new rTypeInstruction(myInstruction));
            break;
        case I_TYPE_OPCODE:
            riscV.execute(new iTypeInstruction(myInstruction));
            break;
        case U_TYPE_OPCODE:
            riscV.execute(new uTypeInstruction(myInstruction));
            break;
        case B_TYPE_OPCODE:
            riscV.execute(new bTypeInstruction(myInstruction));
            break;
        case J_TYPE_OPCODE:
            riscV.execute(new jTypeInstruction(myInstruction));
            break;
    }

    riscV.printState();
    return 0;
}