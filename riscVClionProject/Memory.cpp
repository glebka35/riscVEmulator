//
// Created by Глеб Уваркин on 2019-11-26.
//

#include "Memory.h"

int Memory::write_32(uint32_t addr, int value) {
    if((addr % 4) || (addr < 0))
        return 1;
    uint32_t page = addr & PAGE_MASK;
    uint32_t addrInPage = addr & (!PAGE_MASK);
    auto it = memory.find(page);
    if(it != memory.end()){
        it->second[addrInPage] = value;
    }
    else{
        int* pageAddr = (int*)malloc(sizeof(int) * PAGE_SIZE);
        pageAddr[addrInPage] = value;
        memory.insert(std::pair<uint32_t, int*>(page, pageAddr));
    }
    return 0;
}

int Memory::read_32(uint32_t addr) {
    if((addr % 4) || (addr < 0))
        return 1;

    uint32_t page = addr & PAGE_MASK;
    auto it = memory.find(page);
    if(it != memory.end()){
        return it->second[addr & (!PAGE_MASK)];
    }
    else{
        int* pageAddr = (int*)malloc(sizeof(int) * PAGE_SIZE);
        memory.insert(std::pair<uint32_t, int*>(page, pageAddr));
        return pageAddr[addr & !(PAGE_MASK)];
    }
}

Memory::~Memory() {
    for(auto & it : memory){
        free(it.second);
    }
}

void Memory::printMemory() {
    for(auto & it : memory)
        for(int i = 0; i < PAGE_SIZE; i++)
            std::cout << it.first << ":" << it.second[i] << std::endl;
}
