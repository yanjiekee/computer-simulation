#include "ProgramCounter.h"

ProgramCounter::ProgramCounter()
    :m_register(0)
{}

ProgramCounter::ProgramCounter(uint32_t startingAddress)
    :m_register(startingAddress)
{}

void ProgramCounter::increment() {
    if (m_register == UINT32_MAX)
        m_register = 0;
    else
        m_register++;
    return;
}

void ProgramCounter::jumpTo(uint32_t newAddress) {
    m_register = newAddress;
    return;
}

void ProgramCounter::debug() {
    std::cout << m_register << std::endl;
    return;
}
