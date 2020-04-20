#include "main.h"

#define __DEBUG__

void test_ProgramCounter();

int main() {
    return 0;
}

void test_ProgramCounter() {
    std::cout << "The maximum count of program counter is: "<< UINT32_MAX << '\n' << std::endl;
    ProgramCounter m_programCounter(UINT32_MAX - 10);
    for (int i = 0; i < 20; i++) {
        m_programCounter.increment();
        m_programCounter.debug();
    }
    return;
}
