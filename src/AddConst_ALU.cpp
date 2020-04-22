#include "AddConst_ALU.h"

AddConst_ALU::AddConst_ALU()
    : p_connector(NULL) {
    std::cerr << "ERROR: AddConst_ALU object floating, no connection made" << std::endl;
}

AddConst_ALU::AddConst_ALU(uint32_t *p_bus)
    : m_reg_inputB(4), p_connector(p_bus) {
}

void AddConst_ALU::run() {
    write(*p_connector);
    add();
    *p_connector = read();
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
