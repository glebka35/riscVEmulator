//
// Created by Глеб Уваркин on 2019-11-26.
//

#ifndef RISCVCLIONPROJECT_MEMORY_H
#define RISCVCLIONPROJECT_MEMORY_H

#include <iostream>
#include <map>

#define PAGE_MASK 0xFFFF0000
#define PAGE_SIZE 0x00010000

class Memory {
    std::map<uint32_t, uint32_t*> memory;
public:
    ~Memory();
    int write_32(uint32_t addr, uint32_t value);
    uint32_t read_32(uint32_t addr);

    void printMemory();

};


#endif //RISCVCLIONPROJECT_MEMORY_H
