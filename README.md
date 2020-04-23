# computer-simulation
This is a coursework from ELEC2204 Computer Engineering: Computer Simulation. It is designed to be a simple computer with the specifications listed below.

## how-to

## guidance
Referred from the coursework PDF file.
### specification
1. Implement the basic functionality of a computer in software.
2. Von Neumann architecture (not expecting cache or virtual memory)
3. Follow a straightforward fetch/decode/execute/write-back/memory access cycle.
4. Implement a limited instruction set and register topology, which you may define yourself (you may choose to implement a subset of MIPS instructions). You must not implement a multiply instruction in your processor!
5. Written in C/C++
6. Be tested: you should first test each module, and then write a set of basic test programs that allow you to check that your processor is working as intended; you should also be able to capture the operation of the system, e.g. logging memory accesses.

### task
1. To calculate (and print out) the squares of all the integers between 0 and 99
2. To calculate (and print out) all the prime numbers between 1 and 1000

### hint
- You could consider the most efficient method of implementing the tasks, before deciding on the required functionality of your processor.
- Your processor should run machine code, which should be read-in from a separate input file, but you are free to decide on the instruction set and functionality. You may wish to automate the translation of assembly into machine code. The most able students may even implement a basic C compiler!
- You may wish to automate the production of testing scripts to fully test your system.

## actual design
### specification
1. Bus width of 32 bits, same structure as the MIPS instructions.
2. Memory size of 2^16 words, 1 word = 4 8-bits bytes.
