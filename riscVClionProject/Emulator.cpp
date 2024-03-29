//
// Created by Глеб Уваркин on 2019-11-24.
//

#include "Emulator.h"
#include "Instructions.h"
#include <iostream>
#define COSIM


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
    std::cout << pc << std::endl;
}

void Emulator::execute(rTypeInstruction rType, std::ofstream& R) {
    uint8_t rs1 = rType.rs1;
    uint8_t rs2 = rType.rs2;
    uint8_t rd = rType.rd;
    switch (rType.fullInstruction & R_TYPE_MASK) {
        case add_value:
            x[rd] = x[rs1] + x[rs2];
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
            break;
        case xor_value:
            x[rd] = x[rs1] ^ x[rs2];
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
            break;
        case sub_value:
            x[rd] = x[rs1] - x[rs2];
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
            break;
    }
}

void Emulator::execute(iTypeInstruction iType, std::ofstream& R) {
    uint8_t rs1 = iType.rs1;
    uint32_t imm12 = iType.imm12;
    uint8_t rd = iType.rd;
    switch (iType.fullInstruction & I_TYPE_MASK) {
        case addi_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = x[rs1] + imm12;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
            break;

        case jalr_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = pc + 4;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc = (x[rs1] + imm12) & 0xFFFFFFFE;
            break;
    }
    switch (iType.fullInstruction & I_TYPE_MASK_SHIFT) {
        case slli_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = x[rs1] << imm12;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
            break;

        case srai_value:
            if ((imm12 & 0x800) == 2048){
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = x[rs1] >> imm12;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc+=4;
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

void Emulator::execute(jTypeInstruction jType, std::ofstream& R) {
    uint8_t rd = jType.rd;
    uint32_t imm20 = jType.imm20;
    switch (jType.fullInstruction & J_TYPE_MASK) {
        case jal_value:
            if ((imm20 & 0x80000) == 524288){
                imm20 = imm20 | 0xFFF00000;
            }
            x[rd] = pc + 4;
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
            pc = pc + imm20;
            break;
    }
}

void Emulator::execute(iLoadTypeInstruction iLoadType, std::ofstream& R) {
    uint8_t rs1 = iLoadType.rs1;
    uint32_t imm12 = iLoadType.imm12;
    uint8_t rd = iLoadType.rd;
    switch (iLoadType.fullInstruction & I_TYPE_MASK_LOAD) {
        case lw_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            x[rd] = memory.read_32(x[rs1] + imm12);
            x[0] = 0;
#ifdef COSIM
            for (int i = 0; i < 32; i++) {
                R << x[i] << " ";
            }
            R << std::endl;
#endif
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
            break;
    }
}

void Emulator::execute(bTypeInstruction bType) {
    uint8_t rs1 = bType.rs1;
    uint8_t rs2 = bType.rs2;
    uint32_t imm12 = bType.imm12;
    switch (bType.fullInstruction & B_TYPE_MASK) {
        case blt_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            if (x[rs1] < x[rs2]) {
                pc = pc + imm12;
            } else{
                pc += 4;
            }
            break;

        case beq_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            if (x[rs1] == x[rs2]) {
                pc = pc + imm12;
            } else{
                pc += 4;
            }
            break;

        case bne_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            if (x[rs1] != x[rs2]) {
                pc = pc + imm12;
            } else{
                pc += 4;
            }
            break;

        case bge_value:
            if ((imm12 & 0x800) == 2048) {
                imm12 = imm12 | 0xFFFFF000;
            }
            if (x[rs1] >= x[rs2]) {
                pc = pc + imm12;
            } else{
                pc += 4;
            }
            break;
    }
}

void Emulator::mainExecuteCommands() {
    clock_t start, end;
    start = clock();
    bool isEnd = false;
    int counter = 0;
#ifdef COSIM
    std::ofstream R;
    R.open("functRegisters.txt", std::ios::out);
#endif
    while(!isEnd) {
        uint32_t myInstruction = memory.read_32(pc);

        switch (myInstruction & 0x7F) {
            case R_TYPE_OPCODE:
                execute(getrTypeInstruction(myInstruction), R);
                break;
            case I_TYPE_OPCODE:
                execute(getiTypeInstruction(myInstruction), R);
                break;
            case U_TYPE_OPCODE:
                execute(getuTypeInstruction(myInstruction));
                break;
            case B_TYPE_OPCODE:
                execute(getbTypeInstruction(myInstruction));
                break;
            case J_TYPE_OPCODE:
                execute(getjTypeInstruction(myInstruction), R);
                break;
            case S_TYPE_OPCODE:
                execute(getsTypeInstruction(myInstruction));
                break;
            case I_TYPE_OPCODE_LOAD:
                execute(getiLoadTypeInstruction(myInstruction), R);
            case I_TYPE_OPCODE_JALR:
                execute(getiTypeInstruction(myInstruction), R);
                break;
            default:
                isEnd = true;
                end = clock();
                x[0] = 0;
                double t = ((double)end - start)/((double)CLOCKS_PER_SEC);
                std::cout<<"Unrecognized instruction: " << myInstruction << std::endl;
                std::cout<<"Program counter: " << pc << std::endl;
                std::cout<<"Instructions amount: " << counter << std::endl;
                std::cout<<"Time is " << t << "sec" << std::endl;
                std::cout<<"Speed is " << counter/t/1000000 << " Mill of instr/sec"<<std::endl;
        }
        x[0] = 0;
        counter += 1;
    }
#ifdef COSIM
    R.close();
#endif COSIM
}

void Emulator::printState() {
    for(int i = 0; i < 32; i ++){
        std::cout << "R[" << i << "] = " << x[i] << std::endl;
    }
}

rTypeInstruction Emulator::getrTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(rTypeInstructionCache[i].fullInstruction == instruction)
            return rTypeInstructionCache[i];
    rTypeInstruction newInstruction = rTypeInstruction(instruction);
    rTypeInstructionCache[rTypeIndex] = newInstruction;
    rTypeIndex = (rTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

iTypeInstruction Emulator::getiTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(iTypeInstructionCache[i].fullInstruction == instruction)
            return iTypeInstructionCache[i];
    iTypeInstruction newInstruction = iTypeInstruction(instruction);
    iTypeInstructionCache[iTypeIndex] = newInstruction;
    iTypeIndex = (iTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

uTypeInstruction Emulator::getuTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(uTypeInstructionCache[i].fullInstruction == instruction)
            return uTypeInstructionCache[i];
    uTypeInstruction newInstruction = uTypeInstruction(instruction);
    uTypeInstructionCache[uTypeIndex] = newInstruction;
    uTypeIndex = (uTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

bTypeInstruction Emulator::getbTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(bTypeInstructionCache[i].fullInstruction == instruction)
            return bTypeInstructionCache[i];
    bTypeInstruction newInstruction = bTypeInstruction(instruction);
    bTypeInstructionCache[bTypeIndex] = newInstruction;
    bTypeIndex = (bTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

jTypeInstruction Emulator::getjTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(jTypeInstructionCache[i].fullInstruction == instruction)
            return jTypeInstructionCache[i];
    jTypeInstruction newInstruction = jTypeInstruction(instruction);
    jTypeInstructionCache[jTypeIndex] = newInstruction;
    jTypeIndex = (jTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

sTypeInstruction Emulator::getsTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(sTypeInstructionCache[i].fullInstruction == instruction)
            return sTypeInstructionCache[i];
    sTypeInstruction newInstruction = sTypeInstruction(instruction);
    sTypeInstructionCache[sTypeIndex] = newInstruction;
    sTypeIndex = (sTypeIndex + 1) % CACHE_SIZE;
    return newInstruction;
}

iLoadTypeInstruction Emulator::getiLoadTypeInstruction(uint32_t instruction) {
    for(int i = 0; i < CACHE_SIZE; i++)
        if(iLoadTypeInstructionCache[i].fullInstruction == instruction)
            return iLoadTypeInstructionCache[i];
    iLoadTypeInstruction newInstruction = iLoadTypeInstruction(instruction);
    iLoadTypeInstructionCache[iLoadIndex] = newInstruction;
    iLoadIndex = (iLoadIndex + 1) % CACHE_SIZE;
    return newInstruction;
}
