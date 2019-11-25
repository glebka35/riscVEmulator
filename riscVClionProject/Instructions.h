//
// Created by Глеб Уваркин on 2019-11-25.
//

#ifndef RISCVCLIONPROJECT_INSTRUCTIONS_H
#define RISCVCLIONPROJECT_INSTRUCTIONS_H


#include <cstdint>

#define R_TYPE_OPCODE 0x33
#define I_TYPE_OPCODE 0x13
#define I_TYPE_OPCODE_2     0x03
#define S_TYPE_OPCODE       0x23
#define SB_TYPE_OPCODE      0x63
#define U_TYPE_OPCODE       0x37

#define add_value 0x33
#define R_TYPE_MASK 0xfe00707f


class rTypeInstruction {
public:
    rTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
};

class iTypeInstruction {
public:
    iTypeInstruction(uint32_t instruction);

    uint32_t fullInstruction;
    uint8_t opcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint16_t imm_11_0;
};
#endif //RISCVCLIONPROJECT_INSTRUCTIONS_H
