# Usage:
# make
# make clean

.PHONY = all clean

# Compoler to use
# This is actually a standard variable to indicate that C++ files are compiled
# For C language, it's CC
CXX = g++

# Terminal output messages:
MSG_LINKING = Linking object file...
MSG_COMPILING = Compiling source file...
MSG_CLEANING = Removing all rebuildable files...
MSG_COMPLETE = All done!!

# Warning options (other options: -Wextra -Werror..)
WARNINGS = -Wall

CXXFLAGS = $(WARNINGS) -g

# Virtual path
vpath %.cpp src
vpath %.h include

TARGET = main.out

INCLUDE = -Iinclude

SRC = main.cpp
SRC += test.cpp

OBJ := $(SRC:.cpp=.o)

# Defining files that can be cleaned
REBUILDABLES := $(TARGET) $(OBJ)

all : $(TARGET)
	@echo $(MSG_COMPLETE)

$(TARGET) : $(OBJ)
	@echo $(MSG_LINKING) $^
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile: create object files from C source files.
%.o : %.cpp #%.h
	@echo $(MSG_COMPILING) $<
	$(CXX) $(INCLUDE) $(CXXFLAGS) -c $<

clean :
	@echo $(MSG_CLEANING)
	rm -f $(REBUILDABLES)
