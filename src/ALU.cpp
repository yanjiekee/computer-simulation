#include "ALU.h"

ALU::ALU()
    : m_p_bus_inA(NULL), m_p_bus_inB(NULL), m_p_bus_out(NULL), m_p_g_control(NULL), m_p_alu_control(NULL) {
    std::cerr << "ERROR: ALU object floating, no connection made" << std::endl;
}

ALU::ALU(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out, bool* p_g_control, bool* p_alu_control)
    : m_p_bus_inA(p_bus_inA), m_p_bus_inB(p_bus_inB), m_p_bus_out(p_bus_out), m_p_g_control(p_g_control), m_p_alu_control(p_alu_control) {
}

void ALU::run() {
    m_reg_inputA = *m_p_bus_inA;
    if (m_p_g_control[ALU_SRC]) {
        m_reg_inputB = ((*m_p_bus_inB & I_CONST_ADDR) >> I_CONST_ADDR_SHIFT);
        if (m_reg_inputB >> (16 - 1)) {
            m_reg_inputB = m_reg_inputB | (~I_CONST_ADDR);
        }
        DEBUG_MESSAGE("Input B Bus's Value: %x", m_reg_inputB);
    } else {
        m_reg_inputB = *m_p_bus_inB;
    }
    DEBUG_MESSAGE("Input A: %d", m_reg_inputA);
    DEBUG_MESSAGE("Input B: %d", m_reg_inputB);

    if(m_p_g_control[ALU_OP]) {
        if(m_p_alu_control[ALU_ADD]) {
            add();
            DEBUG_MESSAGE("Operation: Addition");
        }
        else if(m_p_alu_control[ALU_SUB]) {
            sub();
            DEBUG_MESSAGE("Operation: Subtraction");
        }
        else if(m_p_alu_control[ALU_SLT]) {
            sub();
            if (m_reg_output < 0)
                m_reg_output = 1;
            else m_reg_output = 0;

            DEBUG_MESSAGE("Operation: SLT (Sub)");
        }
    } else {
        // Default operation:
        add();
        DEBUG_MESSAGE("Operation (Default): Addition");
    }
    zero_flag = !m_reg_output;
    *m_p_bus_out = m_reg_output;
    DEBUG_MESSAGE("Output: %d", m_reg_output);
    return;
}

void ALU::change_p_bus_inB(uint32_t* p_bus_inB) {
    m_p_bus_inB = p_bus_inB;
    return;
}

void ALU::add() {
    m_reg_output = m_reg_inputA + m_reg_inputB;
    return;
}

void ALU::sub() {
    m_reg_output = m_reg_inputA - m_reg_inputB;
    return;
}
