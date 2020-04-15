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

LINKERFLAG =

# Virtual paths
vpath %.cpp src
vpath %.h include

LINK_TARGET = main.out

# Library directory
INCLUDE = include

ALL_CXXFLAGS = -I$(INCLUDE) $(CXXFLAGS)

SRC = main.cpp
SRC += test.cpp

OBJ := $(SRC:.cpp=.o)

# Defining files that can be cleaned
REBUILDABLES := $(LINK_TARGET) $(OBJ)

all : $(LINK_TARGET)
	@echo $(MSG_COMPLETE)

$(LINK_TARGET) : $(OBJ)
	@echo $(MSG_LINKING) $^
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm -f $(OBJ)

# Compile: create object files from C source files.
%.o : %.cpp %.h
	@echo $(MSG_COMPILING) $<
	$(CXX) $(ALL_CXXFLAGS) -c $<

clean :
	@echo $(MSG_CLEANING)
	rm -f $(REBUILDABLES)
