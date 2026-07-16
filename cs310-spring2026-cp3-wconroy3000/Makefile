# Makefile for CS310 Coding Projects
# Creates proper folder structure: include/, src/, build/, bin/

# User data (add your details here)
COURSE = cs310
SEMESTER = spring2026
LASTNAME = Conroy 
GITHUB_ID = wconroy3000
BU_USERID = wconroy

# CP settings (change this as per the CP you are working on)
# add name of the exe file
CP_NUMBER = 2
EXE = bank

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude
DEPFLAGS = -MMD -MP

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/$(EXE)

# tar name
TAR_NAME = CP$(CP_NUMBER)_$(LASTNAME)_$(BU_USERID)_$(GITHUB_ID).tar.gz

# use all files
ifeq ($(strip $(CPP_FILES)),)
  CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
endif

ifeq ($(strip $(H_FILES)),)
  H_FILES := $(wildcard $(INC_DIR)/*.h)
endif

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))

# Dependency files (generated alongside .o files)
DEPS = $(OBJS:.o=.d)

# Default target
all: directories $(TARGET)

# Create directories if they don't exist
directories:
	@mkdir -p $(SRC_DIR) $(INC_DIR) $(BUILD_DIR) $(BIN_DIR)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile (also generates .d dependency files)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

# Include auto-generated dependency files
-include $(DEPS)

run: all
	./$(TARGET)

# Valgrind
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# GDB
gdb: all
	gdb $(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild
rebuild: clean all

# Setup project structure (moves existing files to proper folders)
setup:
	@if [ -d $(SRC_DIR) ] && [ -d $(INC_DIR) ] && [ -d $(BUILD_DIR) ] && [ -d $(BIN_DIR) ]; then \
		echo "Project structure already exists."; \
	else \
		echo "Creating project structure..."; \
		mkdir -p $(SRC_DIR) $(INC_DIR) $(BUILD_DIR) $(BIN_DIR); \
		mv -f *.h $(INC_DIR)/ 2>/dev/null || true; \
		mv -f *.cpp $(SRC_DIR)/ 2>/dev/null || true; \
		echo "Project structure created:"; \
		echo "  include/ - header files (.h)"; \
		echo "  src/     - source files (.cpp)"; \
		echo "  build/   - object files (.o)"; \
		echo "  bin/     - executable"; \
	fi

	

# for submission
submit: clean
	tar -czvf ../$(TAR_NAME) $(SRC_DIR) $(INC_DIR) Makefile README.md
	@echo "Created submission file: $(TAR_NAME)"
	@echo "Go to the parent folder (cd..) to see the submission file."

.PHONY: all directories run valgrind clean rebuild submit
