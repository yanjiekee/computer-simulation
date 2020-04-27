#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"
// #include "Memory.h"

class ALU_CondBranch {
public:
    ALU_CondBranch();
    ALU_CondBranch(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_out);
    void run();

private:
    int32_t m_reg_inputA;
    int32_t m_reg_inputB;
    int32_t m_reg_output;
    uint32_t* m_p_bus_inA;
    uint32_t* m_p_bus_inB;
    uint32_t* m_p_bus_out;

    void add();
};
