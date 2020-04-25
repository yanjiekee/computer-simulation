#include "Memory.h"

Memory::Memory()
    : m_p_bus_inA(NULL), m_p_bus_inB(NULL), m_p_bus_outA(NULL), m_p_bus_outB(NULL), m_p_g_control(NULL) {
    std::cerr << "ERROR: Memory object floating, no connection made" << std::endl;
}

Memory::Memory(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_outA, uint32_t* p_bus_outB, bool* p_g_control)
    : m_p_bus_inA(p_bus_inA), m_p_bus_inB(p_bus_inB), m_p_bus_outA(p_bus_outA), m_p_bus_outB(p_bus_outB), m_p_g_control(p_g_control) {
    // No need initialise Heap, Stack or Static
    // Store: Reserved & Text section of memory
}

void Memory::run() {
    // Allow lb,sb vs lw,sw
    int dataLength;
    if (m_p_g_control[BYTE_ACCESS]) {
        dataLength = BYTE_LENGTH;
    } else {
        dataLength = WORD_LENGTH;
    }

    if (m_p_g_control[MEM_WRITE]) {
        write(*m_p_bus_inB, *m_p_bus_inA, dataLength);
    }
    else if (m_p_g_control[MEM_READ]) {
        *m_p_bus_outA = read(*m_p_bus_inA, dataLength);
    }
    else if (m_p_g_control[PC_READ]){
        *m_p_bus_outB = read(*m_p_bus_inA, dataLength);
    } else {
        std::cerr << "Memory is not used" << std::endl;
    }
    // Question: Why do we need MEM_READ when we have MEM_WRITE?
}

void Memory::change_p_bus_in(uint32_t* p_bus_inA) {
    m_p_bus_inA = p_bus_inA;
    return;
}

uint32_t Memory::read(uint32_t address, int dataLength) {
    if (dataLength == BYTE_LENGTH) {
        if (address > MEMORY_STACK_UPPERLIMIT_BYTE) {
            std::cerr << "ERROR: Address not within the range of memory" << std::endl;
            return 0;
        }
        DEBUG_MESSAGE("READ: Address: %x, Data: %x", address, m_reg[address]);
        return m_reg[address];
    }
    else if (dataLength == WORD_LENGTH) {
        if (address > MEMORY_STACK_UPPERLIMIT_BYTE - 3) {
            std::cerr << "ERROR: Address not within the range of memory" << std::endl;
            return 0;
        }
        uint32_t word = 0;
        for (int i = 0; i < 4; i++) {
            word = word << 8;
            word += m_reg[address + i];
            DEBUG_MESSAGE("READ: Address: %x, Data: %x", (address + i), m_reg[address + i]);
            // DEBUG_MESSAGE("READ: Current word: %x", word);
        }
        return word;
    } else {
        std::cerr << "ERROR: Access memory only by BYTE or WORD\n" << std::endl;
        return 0;
    }
}

void Memory::write(uint32_t data, uint32_t address, int dataLength) {
    if (dataLength == BYTE_LENGTH) {
        if (address > MEMORY_STACK_UPPERLIMIT_BYTE) {
            std::cerr << "ERROR: Address not within the range of memory" << std::endl;
            return;
        }
        m_reg[address] = (uint8_t)data; // Does it works? Tested and working
        DEBUG_MESSAGE("WRITE: Address: %x, Data: %x", address, m_reg[address]);
    }
    else if (dataLength == WORD_LENGTH) {
        if (address > MEMORY_STACK_UPPERLIMIT_BYTE - 3) {
            std::cerr << "ERROR: Address not within the range of memory" << std::endl;
            return;
        }
        // Use union to cut down word into bytes, because they are in the same memory space
        WordToBytes wordToBytes;
        wordToBytes.word = data;
        for (int i = 0; i < 4; i++) {
            // ToDo: Test this function after decoder is working
            // https://stackoverflow.com/questions/18276225/convert-int-to-short-in-c
            m_reg[address + i] = wordToBytes.byte[3 - i];
            // Index to [4 - i] to be consistent with loading operation
            // The MSB is stored in the byte closest to pointer
            DEBUG_MESSAGE("WRITE: Address: %x, Data: %x", (address + i), wordToBytes.byte[3 - i]);
        }
    } else {
        std::cerr << "ERROR: Access memory only by BYTE or WORD\n" << std::endl;
    }
}
