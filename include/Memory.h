#pragma once

#include <stdint.h>
#include <iostream>
#include <fstream>

#include "debug.h"
#include "InstructionDecoder.h"

#define BYTE_LENGTH 8                   // Based on the type used in m_register array, e.g. uint8_t
#define WORD_LENGTH (4 * BYTE_LENGTH)   // 1 word = 32 bits, size of bus
// #define NO_OF_WORDS (UINT32_MAX + 1)    // INT32_MAX + 1 = 2^32
// #define NO_OF_BYTES (NO_OF_WORDS * BYTE_LENGTH)

// Memory space allocation in bytes (indexing, start at 0)
#define MEMORY_RESERVED_LOWERLIMIT  0x00000000
#define MEMORY_RESERVED_UPPERLIMIT  0x000003ff
#define MEMORY_TEXT_LOWERLIMIT      0x00000400
#define MEMORY_TEXT_UPPERLIMIT      0x000007ff
#define MEMORY_LOG_LOWERLIMIT       0x00000800
#define MEMORY_LOG_UPPERLIMIT       0x00000cff
#define MEMORY_STATIC_LOWERLIMIT    0x00000d00
#define MEMORY_STATIC_UPPERLIMIT    0x00000eff
#define MEMORY_HEAP_LOWERLIMIT      0x00000fff
#define MEMORY_STACK_UPPERLIMIT     0x00001fff


union WordToBytes {
    uint32_t word;
    uint8_t byte[4];
};

class Memory {
public:
    Memory();
    Memory(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_outA, uint32_t* p_bus_outB, bool* p_g_control);
    void run();
    void change_p_bus_in(uint32_t* p_bus_inA);

    void programUpload(std::fstream& text_file, const char* file_location);

private:
    uint8_t m_reg[MEMORY_STACK_UPPERLIMIT + 1];    // Byte addressed
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_outA;
    uint32_t* m_p_bus_outB;
    bool* m_p_g_control;

    uint32_t read(uint32_t address, int dataLength);
    void write(uint32_t data, uint32_t address, int dataLength);
};
