#include "GeneralRegister.h"

GeneralRegister::GeneralRegister()
    : m_p_bus_inA(NULL), m_p_bus_inB(NULL), m_p_bus_outA(NULL), m_p_bus_outB(NULL), m_p_bus_jal(NULL), m_p_g_control(NULL) {
    std::cerr << "ERROR: General Register object floating, no connection made" << std::endl;
}

GeneralRegister::GeneralRegister(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_outA, uint32_t* p_bus_outB, uint32_t* p_bus_jal, bool* p_g_control)
    : m_p_bus_inA(p_bus_inA), m_p_bus_inB(p_bus_inB), m_p_bus_outA(p_bus_outA), m_p_bus_outB(p_bus_outB), m_p_bus_jal(p_bus_jal), m_p_g_control(p_g_control) {
    m_reg[GREG_ZERO] = 0;
    m_reg[GREG_SP] = MEMORY_STACK_UPPERLIMIT;
    m_reg[GREG_FP] = MEMORY_STACK_UPPERLIMIT;
    m_reg[GREG_MP] = MEMORY_LOG_LOWERLIMIT;
}

void GeneralRegister::run() {
    m_read_regA = ((*m_p_bus_inA & REG_SOURCE) >> REG_SOURCE_SHIFT);
    DEBUG_MESSAGE("Read Addr 1: %d", m_read_regA);
    m_read_regB = ((*m_p_bus_inA & REG_TARGET) >> REG_TARGET_SHIFT);
    DEBUG_MESSAGE("Read Addr 2: %d", m_read_regB);
    if(m_p_g_control[REG_DST]) {
        m_write_reg = ((*m_p_bus_inA & REG_DESTINATION) >> REG_DESTINATION_SHIFT);
        DEBUG_MESSAGE("Write Addr: %d .. REG_DST = 1", m_write_reg);
    } else {
        m_write_reg = ((*m_p_bus_inA & REG_TARGET) >> REG_TARGET_SHIFT);
        DEBUG_MESSAGE("Write Addr: %d .. REG_DST = 0", m_write_reg);
    }
    m_write_data = *m_p_bus_inB;

    m_read_dataA = m_reg[m_read_regA];
    m_read_dataB = m_reg[m_read_regB];

    if(m_p_g_control[JUMP_LINK]) {
        m_reg[GREG_RA] = *m_p_bus_jal;
        DEBUG_MESSAGE("New $ra: %x", m_reg[GREG_RA]);
    }
    else if(m_p_g_control[REG_WRITE]) {
        if (m_write_reg == GREG_ZERO) {
            std::cerr << "ERROR: Attempt to rewrite $zero" << std::endl;
            // printf("Bus A: x'%x\n", *m_p_bus_inA);
            // printf("$ra = x'%x\n", m_reg[GREG_RA]);
        }
        m_reg[m_write_reg] = m_write_data;
        DEBUG_MESSAGE("Written Data: %x, Addr: %d", m_reg[m_write_reg], m_write_reg);
    }
    *m_p_bus_outA = m_read_dataA;
    DEBUG_MESSAGE("Read Data 1: %d", m_read_dataA);
    *m_p_bus_outB = m_read_dataB;
    DEBUG_MESSAGE("Read Data 2: %d", m_read_dataB);
}

void GeneralRegister::change_p_bus_inB(uint32_t* p_bus_inB) {
    m_p_bus_inB = p_bus_inB;
    return;
}
