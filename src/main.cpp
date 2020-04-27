#include "main.h"
#include "debug.h"

void test_ProgramCounter();
void test_Memory();
void test_ALU();
void test_greg();
void test_SignExtend();

// Make sure since the whole bus is vulnerable of being modified, only the relevant part is changed when read my a specific module
// Create 5 stages that run continuously (IF, ID, EX, MEM, WB)
int main() {
    debugInit();
    // Buses initialisation:
    uint32_t busA, busB, busC, busD, busE, busF, busG, busH = 0;
    uint32_t *p_bus_if, *p_bus_id, *p_bus_exA, *p_bus_exB, *p_bus_mem, *p_bus_wb, *p_bus_pc_inc, *p_bus_cond_br;
    p_bus_if = &busA;
    p_bus_id = &busB;
    p_bus_exA = &busC;
    p_bus_exB = &busD;
    p_bus_mem = &busE;
    p_bus_wb = &busF;
    p_bus_pc_inc = &busG;
    // ToDo: Try to put p_bus_pc_inc = p_bus_mem once working;
    p_bus_cond_br = &busH;

    // Control flags:
    bool p_g_control[CONTROL_FLAGS_TOTAL];
    bool p_alu_control[ALU_CONTROL_FLAGS_TOTAL];

    // Program (text) memory file:
    std::fstream text_file;

    // Computer modules:
    ProgramCounter pc(p_bus_pc_inc, p_bus_if, p_g_control);
    ALU_IncPC inc_pc_adder(p_bus_if, p_bus_pc_inc);
    Memory mem(p_bus_mem, p_bus_exB, p_bus_wb, p_bus_id, p_g_control);
    mem.programUpload(text_file, "mars/main.txt");
    InstructionDecoder decoder(p_bus_id, p_g_control, p_alu_control);
    GeneralRegister g_reg(p_bus_id, p_bus_mem, p_bus_exA, p_bus_exB, p_bus_pc_inc, p_g_control);
    ALU_CondBranch cond_br_adder(p_bus_pc_inc, p_bus_id, p_bus_cond_br);
    ALU main_alu(p_bus_exA, p_bus_exB, p_bus_mem, p_g_control, p_alu_control);

    for (;;) {
        // printf("\n");
        pc.run();
        pc.change_p_bus_in(p_bus_pc_inc);

        // Stage 1: IF
        p_g_control[PC_READ] = true;
        mem.change_p_bus_in(p_bus_if);
        mem.run();
        p_g_control[PC_READ] = false;
        mem.change_p_bus_in(p_bus_mem);
        inc_pc_adder.run();

        // Stage 2: ID
        if (decoder.run()) {
            std::cout << "TERMINATE: Sequence Ended" << std::endl;
            debugTerminate();
            return 0;
        }
        g_reg.run();

        // Stage 3: EX
        if (p_g_control[ALU_SRC]) {
            main_alu.change_p_bus_inB(p_bus_id);
        }
        main_alu.run();
        main_alu.change_p_bus_inB(p_bus_exB);   // Default ALU source

        // Stage 4: MEM
        mem.run();
        cond_br_adder.run();

        // Stage 5: WB
        if (p_g_control[MEM_TO_REG]) {
            g_reg.change_p_bus_inB(p_bus_wb);
        }
        g_reg.run();
        g_reg.change_p_bus_inB(p_bus_mem);  // Default g.register Write Data connection

        // Mux for PC
        if (p_g_control[JUMP_REG]) {
            DEBUG_MESSAGE("Here");
            pc.change_p_bus_in(p_bus_mem);
        }
        else if (p_g_control[JUMP_UNC]) {
            DEBUG_MESSAGE("Here");
            pc.change_p_bus_in(p_bus_id);
        }
        else if (p_g_control[BRANCH] && main_alu.zero_flag) {
            DEBUG_MESSAGE("Here");
            pc.change_p_bus_in(p_bus_cond_br);
        } else {}
    }

    debugTerminate();
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
    std::fstream text_file;


    printf("value= %x\n", *p_busA);
    printf("value= %x\n", *p_busB);

    Memory ram(p_busA, p_busB, p_busC, p_busC, p_g_control);
    ram.programUpload(text_file, "mars/test.txt");
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

void test_SignExtend() {
    uint32_t m_p_bus_inB = 0x1234D678;
    int32_t m_reg_inputB = ((m_p_bus_inB & I_CONST_ADDR) >> I_CONST_ADDR_SHIFT);
    if (m_reg_inputB >> (16 - 1)) {
        m_reg_inputB = m_reg_inputB | (~I_CONST_ADDR);
    }
    DEBUG_MESSAGE("Before: %x", m_p_bus_inB);
    DEBUG_MESSAGE("After: %x", m_reg_inputB);
}
