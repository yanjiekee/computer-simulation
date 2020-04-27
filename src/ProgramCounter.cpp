#include "ProgramCounter.h"

ProgramCounter::ProgramCounter()
    : m_p_bus_in(NULL), m_p_bus_out(NULL), m_p_g_control(NULL) {
    std::cerr << "ERROR: ProgramCounter object floating, no connection made" << std::endl;
}

ProgramCounter::ProgramCounter(uint32_t* p_bus_in, uint32_t* p_bus_out, bool* p_g_control)
    : m_p_bus_in(p_bus_in), m_p_bus_out(p_bus_out), m_p_g_control(p_g_control) {
    // Initialise the starting of text address
    *m_p_bus_in = MEMORY_TEXT_LOWERLIMIT;
}

// Comment: Unlike other modules, pc is a clocked
// It might be redundant in this simulation because
// it is only necessary when a clock is used
void ProgramCounter::run() {
    write(*m_p_bus_in);
    // "Wait for the clock"
    *m_p_bus_out = read();
    DEBUG_MESSAGE("PC: %d", ((m_reg - MEMORY_TEXT_LOWERLIMIT) / 4) + 1);
    // printf("PC: %d\n", ((m_reg - MEMORY_TEXT_LOWERLIMIT) / 4) + 1);
    return;
}

void ProgramCounter::change_p_bus_in(uint32_t* p_bus_in) {
    m_p_bus_in = p_bus_in;
    return;
}

uint32_t ProgramCounter::read() {
    return m_reg;
}

void ProgramCounter::write(uint32_t newAddress) {
    if (m_p_g_control[JUMP_UNC]) {
        m_reg = (*m_p_bus_in & J_ADDR);
        DEBUG_MESSAGE("Bus in value: x'%x", *m_p_bus_in);
        DEBUG_MESSAGE("Reg value: x'%x", m_reg);
    } else {
        m_reg = *m_p_bus_in;
    }
    if (m_reg > MEMORY_TEXT_UPPERLIMIT) {
        std::cerr << "Error: PC overflow (In data memory)" << std::endl;
    }
}
