//
// Created by Глеб Уваркин on 2019-11-24.
//

#include "Emulator.h"
#include "Instructions.h"
#include <iostream>

Emulator::Emulator() {
    std::cout << "Constructor started" << std::endl;
    // Init registers
    for (int i = 0; i < 32 ; i++) {
        x[i] = 0;
    }

    std::cout << "Constructor finished" << std::endl << "----------------------" << std::endl;;
}

Emulator::~Emulator() {

    std::cout  << "----------------------" << std::endl << "Destructor started" << std::endl;
    std::cout << "Destructor finished" << std::endl;
}

void Emulator::loadProgramToMemory(std::string fileName) {
    uint32_t address;
    uint32_t instruction;
    uint32_t startAddress;
    std::ifstream F;

    F.open(fileName, std::ios::in);
    if (F) {
        F >> startAddress;
        while (!F.eof()) {
            F >> address >> instruction;
            memory.write_32(address, instruction);
        }
    }
    pc = startAddress;
}

void Emulator::execute(rTypeInstruction rType) {
    uint8_t rs1 = rType.rs1;
    uint8_t rs2 = rType.rs2;
    uint8_t rd = rType.rd;
    switch (rType.fullInstruction & R_TYPE_MASK) {
        case add_value:
            x[rd] = x[rs1] + x[rs2];
            pc+=4;
            break;
    }
}

void Emulator::execute(iTypeInstruction iType) {
    uint8_t rs1 = iType.rs1;
    uint32_t imm12 = iType.imm12;
    uint8_t rd = iType.rd;
    switch (iType.fullInstruction & I_TYPE_MASK) {
        case addi_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = x[rs1] + imm12;
            pc+=4;
            break;
        case jalr_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = pc + 4;
            pc = (x[rs1] + imm12) & 0xFFFFFFFE;
            break;
    }

}

void Emulator::execute(uTypeInstruction uType) {
    uint8_t rd = uType.rd;
    uint32_t imm20 = uType.imm20;
    switch (uType.fullInstruction & U_TYPE_MASK) {
        case auipc_value:
//            x[rd] = x[pc] + x[imm20];
            break;
    }
}

void Emulator::execute(jTypeInstruction jType) {
    uint8_t rd = jType.rd;
    uint32_t imm20 = jType.imm20;
    switch (jType.fullInstruction & J_TYPE_MASK) {
        case jal_value:
            if ((imm20 & 0x80000) == 524288){
                imm20 = imm20 | 0xFFF00000;
            }
//            x[pc] = x[pc] + x[imm20];
            break;
    }
}

void Emulator::execute(iLoadTypeInstruction iLoadType) {
    uint8_t rs1 = iLoadType.rs1;
    uint32_t imm12 = iLoadType.imm12;
    uint8_t rd = iLoadType.rd;
    switch (iLoadType.fullInstruction & I_TYPE_MASK_LOAD) {
        case lw_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = memory.read_32(x[rs1] + imm12);
            pc+=4;
            break;
    }
}

void Emulator::execute(sTypeInstruction sType) {
    uint8_t rs1 = sType.rs1;
    uint8_t rs2 = sType.rs2;
    uint32_t imm12 = sType.imm12;
    switch (sType.fullInstruction & S_TYPE_MASK) {
        case sw_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            memory.write_32(x[rs1] + imm12, x[rs2]);
            pc+=4;
    }
}

void Emulator::mainExecuteCommands() {
    bool isEnd = false;
    while(!isEnd) {
        uint32_t myInstruction = memory.read_32(pc);
        switch (myInstruction & 0x7F) {
            case R_TYPE_OPCODE:
                execute(rTypeInstruction(myInstruction));
                break;
            case I_TYPE_OPCODE:
                execute(iTypeInstruction(myInstruction));
                break;
            case U_TYPE_OPCODE:
                execute(uTypeInstruction(myInstruction));
                break;
//        case B_TYPE_OPCODE:
//            execute(new bTypeInstruction(myInstruction));
//            break;
            case J_TYPE_OPCODE:
                execute(jTypeInstruction(myInstruction));
                break;
            case S_TYPE_OPCODE:
                execute(sTypeInstruction(myInstruction));
                break;
            case I_TYPE_OPCODE_LOAD:
                execute(iLoadTypeInstruction(myInstruction));
            case I_TYPE_OPCODE_JALR:
                execute(iTypeInstruction(myInstruction));
                break;
            default:
                isEnd = true;
        }
    }
}

void Emulator::printState() {
    for(int i = 0; i < 32; i ++){
        std::cout << "R[" << i << "] = " << x[i] << std::endl;
    }
}
