#pragma once

#include <stdint.h>
#include <iostream>

#include "debug.h"

// Instructions Format:
#define OPCODE          0b11111100000000000000000000000000
#define REG_SOURCE      0b00000011111000000000000000000000
#define REG_TARGET      0b00000000000111110000000000000000
#define REG_DESTINATION 0b00000000000000001111100000000000
#define SHAMT           0b00000000000000000000011111000000
#define FUNCT           0b00000000000000000000000000111111
#define I_CONST_ADDR    0b00000000000000001111111111111111
#define J_ADDR          0b00000011111111111111111111111111

#define OPCODE_SHIFT            26
#define REG_SOURCE_SHIFT        21
#define REG_TARGET_SHIFT        16
#define REG_DESTINATION_SHIFT   11
#define SHAMT_SHIFT             6
#define FUNCT_SHIFT             0
#define I_CONST_ADDR_SHIFT      0
#define J_ADDR_SHIFT            0

// Instructions:
#define LW      0b100011
#define LB      0b100000
#define SW      0b101011
#define SB      0b101000

#define ADD     0b000000
#define ADDI    0b001000
#define SUB     0b000000

#define SLT     0b000000
#define BEQ     0b000100

#define J       0b000010
#define JAL     0b000011
#define JR      0b000001    // Only one made up

#define R_TYPE  0b000000

// R-Instruction Functions:
#define F_ADD   0b100000
#define F_SUB   0b100010
#define F_SLT   0b101010
#define F_JR    0b001000

// ToDo: Might need to include these to all other classes & main
// General Control Flags:
#define REG_DST     0
#define REG_WRITE   1
#define ALU_SRC     2
#define ALU_OP      3
#define MEM_WRITE   4
#define MEM_READ    5
#define MEM_TO_REG  6
#define BYTE_ACCESS 7
#define BRANCH      8
#define JUMP_UNC    9
#define JUMP_REG    10
#define JUMP_LINK   11
#define PC_READ     12  // To differentiate PC and other modules from reading the memory

#define CONTROL_FLAGS_TOTAL     13   // To define flag array size

// ALU's Control Flags:
#define ALU_ADD 0
#define ALU_SUB 1

#define ALU_CONTROL_FLAGS_TOTAL 2   // To define alu flag array size


// Control's case statements: translating op-code to flags
// Control flags for general purpose & ALU's function
class InstructionDecoder {
public:
    InstructionDecoder();
    InstructionDecoder(uint32_t* p_bus, bool* p_g_control, bool* p_alu_control);
    void run();

private:
    uint32_t m_reg;
    uint32_t* m_p_bus;
    bool* m_p_g_control;
    bool* m_p_alu_control;

    void write(uint32_t instrution);
    uint32_t read();
};
