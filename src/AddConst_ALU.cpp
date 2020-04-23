#include "AddConst_ALU.h"

AddConst_ALU::AddConst_ALU()
    : m_p_bus(NULL), m_p_g_control(NULL) {
    std::cerr << "ERROR: AddConst_ALU object floating, no connection made" << std::endl;
}

AddConst_ALU::AddConst_ALU(uint32_t* p_bus, bool* p_g_control)
    : m_reg_inputB(4), m_p_bus(p_bus), m_p_g_control(p_g_control) {
}

void AddConst_ALU::run() {
    write(*m_p_bus);
    add();
    *m_p_bus = read();
    return;
}

uint32_t AddConst_ALU::read() {
    return m_reg_output;
}

void AddConst_ALU::write(uint32_t newInput) {
    m_reg_inputA = newInput;
    return;
}

void AddConst_ALU::add() {
    m_reg_output = m_reg_inputA + m_reg_inputB;
    return;
}
