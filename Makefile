# Usage:
# make
# make clean

.PHONY = all clean run

# Compoler to use
# This is actually a standard variable to indicate that C++ files are compiled
# For C language, it's CC
CXX = g++

# Terminal output messages:
MSG_LINKING = Linking object file...
MSG_COMPILING = Compiling source file...
MSG_CLEANING = Removing all rebuildable files...
MSG_COMPLETE = All done!!
MSG_RUNNING = Running...

# Warning options (other options: -Wextra -Werror..)
WARNINGS = -Wall

CXXFLAGS = $(WARNINGS) -g

# Virtual path
vpath %.cpp src
vpath %.h include

TARGET = main.out

INCLUDE = -Iinclude

SRC = main.cpp
SRC += CentralProcessingUnit.cpp
SRC += Memory.cpp
SRC += InputOutput.cpp
SRC += Bus.cpp

SRC += Main_ALU.cpp
SRC += InstructionDecoder.cpp
SRC += InstructionRegister.cpp
SRC += ProgramCounter.cpp
SRC += GeneralRegister.cpp
SRC += AddConst_ALU.cpp
SRC += Add_ALU.cpp

SRC += debug.cpp

OBJ := $(SRC:.cpp=.o)

# Defining files that can be cleaned
REBUILDABLES := $(TARGET) $(OBJ)

all : $(TARGET)
	@echo
	@echo $(m)

$(TARGET) : $(OBJ)
	@echo
	@echo $(MSG_LINKING) $^
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile: create object files from C source files.
%.o : %.cpp #%.h
	@echo
	@echo $(MSG_COMPILING) $<
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c $<

clean :
	@echo
	@echo $(MSG_CLEANING)
	rm -f $(REBUILDABLES)
	clear

run :
	@echo
	@echo $(MSG_RUNNING)
	./main.out
