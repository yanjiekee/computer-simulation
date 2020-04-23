#include <stdint.h>
#include <iostream>

#include "debug.h"

// Adding input with constant 4 (length of a word in bytes)
// m_reg_inputB is initialised in constructor
class AddConst_ALU {
public:
    AddConst_ALU();
    AddConst_ALU(uint32_t* p_bus, bool* p_g_control);
    void run();

private:
    uint32_t m_reg_inputA;
    uint32_t m_reg_inputB;
    uint32_t m_reg_output;
    uint32_t* m_p_bus;
    bool* m_p_g_control;

    uint32_t read();
    void write(uint32_t newInput);
    void add();
};