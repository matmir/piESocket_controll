CC		:= g++
CFLAGS	:= -Wall -std=c++14
LDFLAGS	:= -lgpiod -lpthread -lrt -lonhSHMcpp
INCLUDE	:= 

BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/app

TARGET   := eSocket

SRC :=														\
	$(wildcard src/*.cpp)									\
	$(wildcard src/utils/*.cpp)								\
	$(wildcard src/program/*.cpp)								\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

DEPS := $(OBJECTS:%.o=%.d)

-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

all: build $(APP_DIR)/$(TARGET)
	cd test; make all

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	
debug: CFLAGS += -DDEBUG -g
debug: build $(APP_DIR)/$(TARGET)
	cd test; make debug

release: CFLAGS += -O2
release: build $(APP_DIR)/$(TARGET)
	cd test; make release

clean:
	-@rm -rf $(BUILD)
	cd test; make clean
	
.PHONY: all build clean debug release

