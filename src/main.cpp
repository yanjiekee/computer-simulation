#include "main.h"
#include "debug.h"

void test_ProgramCounter();
void test_Memory();
void test_ALU();
void test_greg();

// Make sure since the whole bus is vulnerable of being modified, only the relevant part is changed when read my a specific module
// Create 5 stages that run continuously (IF, ID, EX, MEM, WB)
int main() {
    // Buses initialisation:
    uint32_t *p_bus_if;
    uint32_t *p_bus_id;
    uint32_t *p_bus_ex;
    uint32_t *p_bus_mem;
    uint32_t *p_bus_wb;
    uint32_t *p_bus_pc_inc;
    uint32_t *p_bus_cond_br;




    return 0;
}

void test_ProgramCounter() {
    uint32_t *p_bus;
    uint32_t bus = 0;
    p_bus = &bus;
    uint32_t *p_busB;
    uint32_t busB = 4;
    p_busB = &busB;


    bool p_g_control[CONTROL_FLAGS_TOTAL];
    bool p_alu_control[ALU_CONTROL_FLAGS_TOTAL];

    ProgramCounter pc(p_bus, p_bus, p_g_control);
    ALU adder(p_bus, p_busB, p_bus, p_g_control, p_alu_control);
    pc.run();
    adder.run();
    pc.run();

    return;
}

void test_Memory() {
    uint32_t *p_busA;
    uint32_t *p_busB;
    uint32_t *p_busC;
    uint32_t busA = 0x00000122;
    uint32_t busB = 0x00000011;
    uint32_t busC = 0;
    p_busA = &busA;
    p_busB = &busB;
    p_busC = &busC;
    bool p_g_control[CONTROL_FLAGS_TOTAL];
    // bool p_alu_control[ALU_CONTROL_FLAGS_TOTAL];

    printf("value= %x\n", *p_busA);
    printf("value= %x\n", *p_busB);

    Memory ram(p_busA, p_busB, p_busC, p_busC, p_g_control);
    // Notes: Read and write function now moved to private after testing
    // ram.write(0x12345678, 0, WORD_LENGTH);
    // uint32_t a = ram.read(0, WORD_LENGTH);
    // printf("Final read value= %x\n", a);

    p_g_control[BYTE_ACCESS] = true;
    p_g_control[MEM_WRITE] = false;
    p_g_control[MEM_READ] = false;
    ram.run();
    p_g_control[MEM_WRITE] = true;
    ram.run();
    p_g_control[MEM_WRITE] = false;
    p_g_control[MEM_READ] = true;
    ram.run();

    return;
}

void test_ALU() {
    uint32_t *p_busA;
    uint32_t *p_busB;
    uint32_t *p_busC;
    uint32_t busA = 0x00000122;
    uint32_t busB = 0x00000011;
    uint32_t busC = 0;
    p_busA = &busA;
    p_busB = &busB;
    p_busC = &busC;
    bool p_g_control[CONTROL_FLAGS_TOTAL];
    bool p_alu_control[ALU_CONTROL_FLAGS_TOTAL];

    ALU alu(p_busA, p_busB, p_busC, p_g_control, p_alu_control);
    p_g_control[ALU_OP] = false;
    p_alu_control[ALU_ADD] = false;
    p_alu_control[ALU_SUB] = false;
    alu.run();
    p_g_control[ALU_OP] = true;
    p_alu_control[ALU_SUB] = true;
    alu.run();

    return;
}

void test_greg() {
    uint32_t *p_busA;
    uint32_t *p_busB;
    uint32_t *p_busB2;
    uint32_t *p_busC;
    uint32_t *p_busD;
    uint32_t *p_busJAL;
    uint32_t busA = 0b00000000101010001011100000000000;
    uint32_t busB = 0x12345678;
    uint32_t busB2 = 0x87654321;
    uint32_t busC = 0x01010101;
    uint32_t busD = 0x10101010;
    uint32_t busJAL = 0x40000600;
    p_busA = &busA;
    p_busB = &busB;
    p_busB2 = &busB2;
    p_busC = &busC;
    p_busD = &busD;
    p_busJAL = &busJAL;
    bool p_g_control[CONTROL_FLAGS_TOTAL];
    // bool p_alu_control[ALU_CONTROL_FLAGS_TOTAL];

    GeneralRegister greg(p_busA, p_busB, p_busC, p_busD, p_busJAL, p_g_control);
    // Default:
    p_g_control[REG_DST] = false;
    p_g_control[REG_WRITE] = false;
    p_g_control[JUMP_LINK] = false;
    greg.run();
    DEBUG_MESSAGE("-------------------------");
    p_g_control[REG_DST] = true;
    greg.run();
    DEBUG_MESSAGE("-------------------------");
    p_g_control[REG_WRITE] = true;
    greg.run();
    DEBUG_MESSAGE("-------------------------");
    greg.change_p_bus_inB(p_busB2);
    greg.run();
    DEBUG_MESSAGE("-------------------------");
    p_g_control[REG_WRITE] = false;
    p_g_control[JUMP_LINK] = true;
    greg.run();
    return;
}
