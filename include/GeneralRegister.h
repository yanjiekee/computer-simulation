#include <stdint.h>
#include <iostream>

#include "debug.h"
#include "InstructionDecoder.h"

// Definition not very useful
#define GREG_ZERO   0
#define GREG_AT     1
#define GREG_V0     2
#define GREG_V1     3
#define GREG_A0     4
#define GREG_A1     5
#define GREG_A2     6
#define GREG_A3     7
#define GREG_T0     8
#define GREG_T1     9
#define GREG_T2     10
#define GREG_T3     11
#define GREG_T4     12
#define GREG_T5     13
#define GREG_T6     14
#define GREG_T7     15
#define GREG_S0     16
#define GREG_S1     17
#define GREG_S2     18
#define GREG_S3     19
#define GREG_S4     20
#define GREG_S5     21
#define GREG_S6     22
#define GREG_S7     23
#define GREG_T8     24
#define GREG_T9     25
#define GREG_K0     26
#define GREG_K1     27
#define GREG_GP     28
#define GREG_SP     29
#define GREG_FP     30
#define GREG_RA     31

#define REG_NUM 32

class GeneralRegister {
public:
    GeneralRegister();
    GeneralRegister(uint32_t* p_bus_inA, uint32_t* p_bus_inB, uint32_t* p_bus_outA, uint32_t* p_bus_outB, uint32_t* p_bus_jal, bool* p_g_control);
    void run();
    void change_p_bus_inB(uint32_t* p_bus_inB);

private:
    uint32_t m_reg[REG_NUM];
    uint32_t* m_p_bus_inA;  // RRA, RRB, WR
    uint32_t* m_p_bus_inB;  // WD
    uint32_t* m_p_bus_outA; // RR1
    uint32_t* m_p_bus_outB; // RR2
    uint32_t* m_p_bus_jal;
    bool* m_p_g_control;


    // All the uint8_t are actually only 5 bits
    uint8_t m_read_regA;
    uint32_t m_read_dataA;

    uint8_t m_read_regB;
    uint32_t m_read_dataB;

    uint8_t m_write_reg;
    uint32_t m_write_data;
};
