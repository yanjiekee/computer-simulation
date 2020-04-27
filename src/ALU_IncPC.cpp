#include "ALU_IncPC.h"

ALU_IncPC::ALU_IncPC()
    : m_p_bus_in(NULL), m_p_bus_out(NULL) {
    std::cerr << "ERROR: ALU_IncPC object floating, no connection made" << std::endl;
}

ALU_IncPC::ALU_IncPC(uint32_t* p_bus_in, uint32_t* p_bus_out)
    : m_p_bus_in(p_bus_in), m_p_bus_out(p_bus_out) {
    m_reg_inputB = 4;
}

void ALU_IncPC::run() {
    m_reg_inputA = *m_p_bus_in;
    // DEBUG_MESSAGE("Input: %x", m_reg_inputA);

    add();
    // DEBUG_MESSAGE("Operation (Default): Addition");

    *m_p_bus_out = m_reg_output;
    // DEBUG_MESSAGE("Output: %x", m_reg_output);
    return;
}

void ALU_IncPC::add() {
    m_reg_output = m_reg_inputA + m_reg_inputB;
    return;
}
