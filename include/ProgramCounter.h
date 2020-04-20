#include <stdint.h>
#include <iostream>

class ProgramCounter {
public:
    ProgramCounter();
    ProgramCounter(uint32_t startingAddress);
    void increment();
    void jumpTo(uint32_t newAddress);
    void debug();
    
private:
    uint32_t m_register;
};
