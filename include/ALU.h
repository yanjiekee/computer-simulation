#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"
#include "Memory.h"

class ALU {
public:
    ALU();
    ALU(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out, bool* p_g_control, bool* p_alu_control);
    void run();
    void change_p_bus_inB(uint32_t* p_bus_inB);

    bool zero_flag;

private:
    int32_t m_reg_inputA;
    int32_t m_reg_inputB;
    int32_t m_reg_output;
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_out;
    bool* m_p_g_control;
    bool* m_p_alu_control;

    void add();
    void sub();
};
