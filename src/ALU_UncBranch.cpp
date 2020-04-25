#include "ALU_UncBranch.h"

ALU_UncBranch::ALU_UncBranch()
    : m_p_bus_inA(NULL), m_p_bus_inB(NULL), m_p_bus_out(NULL) {
    std::cerr << "ERROR: ALU_UncBranch object floating, no connection made" << std::endl;
}

ALU_UncBranch::ALU_UncBranch(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out)
    : m_p_bus_inA(p_bus_inA), m_p_bus_inB(p_bus_inB), m_p_bus_out(p_bus_out) {
}

void ALU_UncBranch::run() {
    m_reg_inputA = *m_p_bus_inA;
    m_reg_inputB = *m_p_bus_inB;
    DEBUG_MESSAGE("Input A: %x", m_reg_inputA);
    DEBUG_MESSAGE("Input B: %x", m_reg_inputB);

    add();
    DEBUG_MESSAGE("Operation (Default): Addition");

    *m_p_bus_out = m_reg_output;
    DEBUG_MESSAGE("Output: %x", m_reg_output);
    return;
}

void ALU_UncBranch::add() {
    m_reg_output = m_reg_inputA + m_reg_inputB;
    return;
}
