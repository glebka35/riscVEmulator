//
// Created by Глеб Уваркин on 2019-11-25.
//

#include "Instructions.h"

rTypeInstruction::rTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    rs2 = (instruction >> 20) & 0x1F;
    funct7 = (instruction >> 25) & 0x7F;
}

iTypeInstruction::iTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    funct3 = (instruction >> 12) & 0x3;
    rs1 = (instruction >> 15) & 0x1F;
    imm_11_0 = (instruction >> 20) & 0x3FF;
}

uTypeInstruction::uTypeInstruction(uint32_t instruction) {
    fullInstruction = instruction;
    opcode = instruction & 0x7F;
    rd = (instruction >> 7) & 0x1F;
    imm_31_12 = (instruction >> 12) & 0xFFFFF;
}