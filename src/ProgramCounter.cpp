#include "ProgramCounter.h"

// Empty constructor: members are not initialised, can be any value
ProgramCounter::ProgramCounter()
    : m_p_bus(NULL), m_p_controlFlags(NULL) {
    std::cerr << "ERROR: ProgramCounter object floating, no connection made" << std::endl;
}

ProgramCounter::ProgramCounter(uint32_t* p_bus, bool* p_controlFlags)
    : m_p_bus(p_bus), m_p_controlFlags(p_controlFlags) {
}

// Comment: Unlike other modules, pc is a clocked
// It might be redundant in this simulation because
// it is only necessary when a clock is used
void ProgramCounter::run() {
    write(*m_p_bus);
    // "Wait for the clock"
    *m_p_bus = read();
    DEBUG_MESSAGE("PC: %d", m_reg);

    return;
}

uint32_t ProgramCounter::read() {
    return m_reg;
}

void ProgramCounter::write(uint32_t newAddress) {
    if (newAddress > MEMORY_TEXT_UPPERLIMIT)
        std::cerr << "Error: PC overflow (In data memory)" << std::endl;
    else
        m_reg = newAddress;
}
