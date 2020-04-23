#include "InstructionDecoder.h"

InstructionDecoder::InstructionDecoder()
    : m_p_bus(NULL), m_p_g_control(NULL), m_p_alu_control(NULL) {
    std::cerr << "ERROR: InstructionDecoder object floating, no connection made\n" << std::endl;
}

InstructionDecoder::InstructionDecoder(uint32_t* p_bus, bool* p_g_control, bool* p_alu_control)
    : m_p_bus(p_bus), m_p_g_control(p_g_control), m_p_alu_control(p_alu_control) {
}

void InstructionDecoder::run() {
    // Reset control flags:
    for (int i = 0; i < CONTROL_FLAGS_TOTAL; i++) {
        m_p_g_control[i] = false;
    }
    for (int i = 0; i < ALU_CONTROL_FLAGS_TOTAL; i++) {
        m_p_alu_control[i] = false;
    }

    write(*m_p_bus);
    uint32_t opcode = m_reg & OPCODE;
    opcode = opcode >> OPCODE_SHIFT;
    switch(opcode) {
        case R_TYPE : {  // SUB, SLT, ADD, JR
            uint32_t funct = m_reg & FUNCT;
            funct = funct >> FUNCT_SHIFT;
            switch(funct) {
                case F_ADD: {
                    m_p_alu_control[ALU_ADD] = true;
                    break;
                }
                case F_SUB: {
                    m_p_alu_control[ALU_SUB] = true;
                    break;
                }
                case F_SLT: {
                    m_p_alu_control[ALU_SUB] = true;
                    break;
                }
                default:
                    std::cerr << "ERROR: R-Instr Function Not Recognised\n" << std::endl;
            }
            m_p_g_control[ALU_OP] = true;
            break;
        }
        case LW: {
            m_p_g_control[ALU_SRC] = true;
            m_p_g_control[MEM_READ] = true;
            m_p_g_control[REG_WRITE] = true;
            m_p_g_control[MEM_TO_REG] = true;
            break;
        }
        case LB: {
            m_p_g_control[ALU_SRC] = true;
            m_p_g_control[MEM_READ] = true;
            m_p_g_control[REG_WRITE] = true;
            m_p_g_control[MEM_TO_REG] = true;
            m_p_g_control[BYTE_ACCESS] = true;
            break;
        }
        case SW: {
            m_p_g_control[ALU_SRC] = true;
            m_p_g_control[MEM_WRITE] = true;
            m_p_g_control[REG_DST] = true;
            break;
        }
        case SB: {
            m_p_g_control[ALU_SRC] = true;
            m_p_g_control[MEM_WRITE] = true;
            m_p_g_control[BYTE_ACCESS] = true;
            m_p_g_control[REG_DST] = true;
            break;
        }
        case ADDI: {
            m_p_g_control[ALU_SRC] = true;
            m_p_g_control[REG_DST] = true;
            break;
        }
        case BEQ: {
            m_p_g_control[BRANCH] = true;
            m_p_g_control[REG_DST] = true;
            m_p_g_control[ALU_OP] = true;

            m_p_alu_control[ALU_SUB] = true;
            break;
        }
        case J: {
            m_p_g_control[JUMP_UNC] = true;
            break;
        }
        case JR: {
            m_p_g_control[JUMP_REG] = true;
            break;
        }
        case JAL: {
            m_p_g_control[JUMP_LINK] = true;
            m_p_g_control[REG_WRITE] = true;
            break;
        }
        default :
            std::cerr << "ERROR: Opcode Not Recognised\n" << std::endl;
    }
    return;
}

void InstructionDecoder::write(uint32_t instrution) {
    m_reg = instrution;
}

uint32_t InstructionDecoder::read() {
    return m_reg;
}
