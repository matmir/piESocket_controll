CC		:= g++
CFLAGS	:= -Wall -std=c++17
LDFLAGS	:= -lgtest -lpthread -lrt 
INCLUDE	:= -I"../src/program" -I"../src/utils"

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := eSocket_test

SRC :=														\
	$(wildcard src/*.cpp)									\
	$(wildcard ../src/program/*.cpp) 						\
	$(wildcard ../src/utils/*.cpp) 							\

VPATH := $(dir $(SRC))
OBJECTS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

all: build $(APP_DIR)/$(TARGET)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	
debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O2
release: all

clean:
	-@rm -rf $(BUILD)
	
.PHONY: all build clean debug release

