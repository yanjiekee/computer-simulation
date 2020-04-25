#include <stdint.h>
#include <iostream>

#include "debug.h"
// #include "InstructionDecoder.h"

class ALU_IncPC {
public:
    ALU_IncPC();
    ALU_IncPC(uint32_t* p_bus_in, uint32_t* p_bus_out);
    void run();

private:
    int32_t m_reg_inputA;
    int32_t m_reg_inputB;
    int32_t m_reg_output;
    uint32_t* m_p_bus_in;
    uint32_t* m_p_bus_out;

    void add();
};
