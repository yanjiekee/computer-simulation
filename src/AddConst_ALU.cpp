#include "AddConst_ALU.h"

AddConst_ALU::AddConst_ALU()
    : m_p_bus_in(NULL), m_p_bus_out(NULL), m_p_g_control(NULL) {
    std::cerr << "ERROR: AddConst_ALU object floating, no connection made" << std::endl;
}

AddConst_ALU::AddConst_ALU(uint32_t* p_bus_in, uint32_t* p_bus_out, bool* p_g_control)
    : m_reg_inputB(4), m_p_bus_in(p_bus_in), m_p_bus_out(p_bus_out), m_p_g_control(p_g_control) {
}

void AddConst_ALU::run() {
    write(*m_p_bus_in);
    add();
    *m_p_bus_out = read();
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
