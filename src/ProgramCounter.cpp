#include "ProgramCounter.h"

// Empty constructor: members are not initialised, can be any value
ProgramCounter::ProgramCounter()
    : p_connector(NULL) {
    std::cerr << "ERROR: ProgramCounter object floating, no connection made" << std::endl;
}

ProgramCounter::ProgramCounter(uint32_t *p_bus)
    : p_connector(p_bus) {
}

// Comment: Unlike other modules, pc is a clocked
// It might be redundant in this simulation because
// it is only necessary when a clock is used
void ProgramCounter::run() {
    write(*p_connector);
    // "Wait for the clock"
    *p_connector = read();
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
