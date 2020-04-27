#include "ALU_CondBranch.h"

ALU_CondBranch::ALU_CondBranch()
    : m_p_bus_inA(NULL), m_p_bus_inB(NULL), m_p_bus_out(NULL) {
    std::cerr << "ERROR: ALU_CondBranch object floating, no connection made" << std::endl;
}

ALU_CondBranch::ALU_CondBranch(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out)
    : m_p_bus_inA(p_bus_inA), m_p_bus_inB(p_bus_inB), m_p_bus_out(p_bus_out) {
}

void ALU_CondBranch::run() {
    m_reg_inputA = *m_p_bus_inA;

    // Sign Extend:
    m_reg_inputB = ((*m_p_bus_inB & I_CONST_ADDR) >> I_CONST_ADDR_SHIFT);
    if (m_reg_inputB >> (16 - 1)) {
        m_reg_inputB = m_reg_inputB | (~I_CONST_ADDR);
    }
    // DEBUG_MESSAGE("Input A: %d", m_reg_inputA);
    // DEBUG_MESSAGE("Input B: %d", m_reg_inputB);

    add();
    // DEBUG_MESSAGE("Operation (Default): Addition");

    *m_p_bus_out = m_reg_output;
    // DEBUG_MESSAGE("Output: %d", m_reg_output);
    return;
}

void ALU_CondBranch::add() {
    m_reg_output = m_reg_inputA + m_reg_inputB;
    return;
}
