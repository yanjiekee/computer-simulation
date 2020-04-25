#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"

class ALU_UncBranch {
public:
    ALU_UncBranch();
    ALU_UncBranch(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out);
    void run();

private:
    uint32_t m_reg_inputA;
    uint32_t m_reg_inputB;
    uint32_t m_reg_output;
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_out;

    void add();
};
