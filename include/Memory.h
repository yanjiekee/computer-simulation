#pragma once

#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"

#define BYTE_LENGTH 8                   // Based on the type used in m_register array, e.g. uint8_t
#define WORD_LENGTH (4 * BYTE_LENGTH)   // 1 word = 32 bits, size of bus
#define NO_OF_WORDS (UINT32_MAX + 1)    // INT32_MAX + 1 = 2^32
#define NO_OF_BYTES (NO_OF_WORDS * BYTE_LENGTH)

// Memory space allocation in bits (indexing, start at 0)
#define MEMORY_RESERVED_LOWERLIMIT  0x00000000
#define MEMORY_RESERVED_UPPERLIMIT  0x003fffff
#define MEMORY_TEXT_LOWERLIMIT      0x00400000
#define MEMORY_TEXT_UPPERLIMIT      0x0fffffff
#define MEMORY_STATIC_LOWERLIMIT    0x10000000
#define MEMORY_STATIC_UPPERLIMIT    0x1000ffff
#define MEMORY_HEAP_LOWERLIMIT      0x10010000
#define MEMORY_STACK_UPPERLIMIT     0x7fffffff

// Memory space allocation in bytes (indexing)
#define MEMORY_RESERVED_LOWERLIMIT_BYTE 0x00000000
#define MEMORY_RESERVED_UPPERLIMIT_BYTE 0x0007ffff
#define MEMORY_TEXT_LOWERLIMIT_BYTE     0x00080000
#define MEMORY_TEXT_UPPERLIMIT_BYTE     0x01ffffff
#define MEMORY_STATIC_LOWERLIMIT_BYTE   0x02000000
#define MEMORY_STATIC_UPPERLIMIT_BYTE   0x02001fff
#define MEMORY_HEAP_LOWERLIMIT_BYTE     0x02002000
#define MEMORY_STACK_UPPERLIMIT_BYTE    0x0fffffff

union WordToBytes {
    uint32_t word;
    uint8_t byte[4];
};

class Memory {
public:
    Memory();
    Memory(uint32_t* p_bus_inA, uint32_t* p_busB, uint32_t* p_bus_outA, uint32_t* p_bus_outB, bool* p_g_control);
    void run();
    void change_p_bus_in(uint32_t* p_bus_inA);

private:
    uint8_t m_reg[NO_OF_BYTES];    // Byte addressed
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_outA;
    uint32_t* m_p_bus_outB;
    bool* m_p_g_control;

    uint32_t read(uint32_t address, int dataLength);
    void write(uint32_t data, uint32_t address, int dataLength);
};
