#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"

// Adding input with constant 4 (length of a word in bytes)
// m_reg_inputB is initialised in constructor
class ALU {
public:
    ALU();
    ALU(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out, bool* p_g_control, bool* p_alu_control);
    void run();

    bool zero_flag;

private:
    uint32_t m_reg_inputA;
    uint32_t m_reg_inputB;
    uint32_t m_reg_output;
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_out;
    bool* m_p_g_control;
    bool* m_p_alu_control;

    void add();
    void sub();
};
