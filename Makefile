#--------------------------------------------------------
# system
#--------------------------------------------------------
UNAME = $(shell uname)

#--------------------------------------------------------
# target
#--------------------------------------------------------
TARGET = libfrucht

#--------------------------------------------------------
# directories
#--------------------------------------------------------
SRC_DIR = ./src/
INC_DIR = ./include/

BIN_DIR = ./bin/

OBJ_DIR = ./obj/$(UNAME)/
OBJ32_DIR = $(OBJ_DIR)32bit/
OBJ64_DIR = $(OBJ_DIR)64bit/

ifneq ($(UNAME), Linux)
SDL_DIR   = E:/SDL2/
SDL32_DIR = $(SDL_DIR)i686-w64-mingw32/
SDL64_DIR = $(SDL_DIR)x86_64-w64-mingw32/
endif

#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX = g++

ifeq ($(UNAME), Linux)
INCLUDE   = -I$(INC_DIR)
LFLAGS    = -lSDL2 -lGL -lGLEW
else
INCLUDE32 = -I$(INC_DIR) -I$(SDL32_DIR)include/
INCLUDE64 = -I$(INC_DIR) -I$(SDL64_DIR)include/
LFLAGS32  = -L$(SDL32_DIR)lib/ -lm -lmingw32 -lSDL2main -lSDL2 -lGL -lGLEW
LFLAGS64  = -L$(SDL64_DIR)lib/ -lm -lmingw32 -lSDL2main -lSDL2 -lGL -lGLEW
endif

ifeq ($(UNAME), Linux)
CFLAGS    = -MD -MP -pedantic -std=c++11 -O2 -fPIC
else
CFLAGS    = -MD -MP -pedantic -std=c++11 -O2
endif
CFLAGS32  = -m32 $(CFLAGS)
CFLAGS64  = -m64 $(CFLAGS)

#--------------------------------------------------------
# sources
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
else
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,$(SRC_DIR),*.cpp)
endif

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS32 = $(patsubst $(SRC_DIR)%.cpp, $(OBJ32_DIR)%.o, $(SOURCES))
OBJECTS64 = $(patsubst $(SRC_DIR)%.cpp, $(OBJ64_DIR)%.o, $(SOURCES))

DEPS32	= $(OBJECTS32:.o=.d)
DEPS64	= $(OBJECTS64:.o=.d)

#--------------------------------------------------------
# make all rule
#--------------------------------------------------------
all: frucht64

#--------------------------------------------------------
# frucht rules
#--------------------------------------------------------
ifeq ($(UNAME), Linux)
frucht32: $(BIN_DIR)$(TARGET).l32.so
frucht64: $(BIN_DIR)$(TARGET).l64.so
else
frucht32: $(BIN_DIR)$(TARGET).w32.dll
frucht64: $(BIN_DIR)$(TARGET).w64.dll
endif

#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ32_DIR)
	rm -rf $(OBJ64_DIR)
ifeq ($(UNAME), Linux)
	rm -rf $(BIN_DIR)$(TARGET).l32.so
	rm -rf $(BIN_DIR)$(TARGET).l64.so
else
	rm -rf $(BIN_DIR)$(TARGET).w32.dll
	rm -rf $(BIN_DIR)$(TARGET).w64.dll
endif

#--------------------------------------------------------
# frucht objects and target rules
#--------------------------------------------------------

ifeq ($(UNAME), Linux)
$(BIN_DIR)$(TARGET).l32.so: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) -shared $^ -o $@ $(CFLAGS32) $(LFLAGS)
$(BIN_DIR)$(TARGET).l64.so: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) -shared $^ -o $@ $(CFLAGS64) $(LFLAGS)
else
$(BIN_DIR)$(TARGET).w32.dll: $(OBJECTS32)
	@mkdir -p $(@D)
	$(CXX) -shared $^ -o $@ $(CFLAGS32) $(LFLAGS32)
$(BIN_DIR)$(TARGET).w64.dll: $(OBJECTS64)
	@mkdir -p $(@D)
	$(CXX) -shared $^ -o $@ $(CFLAGS64) $(LFLAGS64)
endif

-include $(DEPS32)
-include $(DEPS64)

ifeq ($(UNAME), Linux)
$(OBJ32_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE) $< -o $@
else
$(OBJ32_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS32) $(INCLUDE32) $< -o $@
endif

ifeq ($(UNAME), Linux)
$(OBJ64_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE) $< -o $@
else
$(OBJ64_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS64) $(INCLUDE64) $< -o $@
endif
