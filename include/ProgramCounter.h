#include <stdint.h>
#include <iostream>

#include "debug.h"

#define MEMORY_TEXT_UPPERLIMIT 0x0fffffff

class ProgramCounter {
public:
    ProgramCounter();
    ProgramCounter(uint32_t* p_bus_in, uint32_t* p_bus_out, bool* p_g_control);
    void run();
    void change_p_bus_in(uint32_t* p_bus_in);

private:
    uint32_t m_reg;
    uint32_t* m_p_bus_in;
    uint32_t* m_p_bus_out;
    bool* m_p_g_control;

    uint32_t read();
    void write(uint32_t newAddress);
};
