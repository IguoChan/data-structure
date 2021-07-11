# define the target
TARGET = data-structure

# define the Build Directory
BUILD_DIR = build
OBJ_DIR := $(BUILD_DIR)/objs
DEP_DIR := $(BUILD_DIR)/deps

# define PATH
LOCAL_PATH = $(shell pwd)

# define the sources and objects
SOURCES := $(shell find $(LOCAL_PATH)/ -name "*.c")
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(notdir $(SOURCES))))
DEPS := $(addprefix $(DEP_DIR)/, $(patsubst %.c, %.d, $(notdir $(SOURCES))))

# define VPATH
VPATH = $(LOCAL_PATH):$(LOCAL_PATH)/list/:$(LOCAL_PATH)/queue/

# define the includes, compile and link flags
INCLUDES := -I$(LOCAL_PATH) -I$(LOCAL_PATH)/list/ -I$(LOCAL_PATH)/queue/
CC_FLAGS := -g $(INCLUDES)

# define the compiler
CC = gcc

# define the phony target
.PHONY : all clean

# build the target 
all: $(BUILD_DIR)/$(TARGET)
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi;\
	$(CC) $^ $(LK_FLAGS) -o $@

# build the objects
$(OBJ_DIR)/%.o : %.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
	$(CC) -c $(CC_FLAGS) -o $@ $<

# build the dependencies
$(DEP_DIR)/%.d : %.c
	@if [ ! -d $(DEP_DIR) ]; then mkdir -p $(DEP_DIR); fi;\
	set -e; rm -f $@;\
	$(CC) -MM $(CC_FLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

# when *.h file changes, remake the project
-include $(DEPS)

# clean all products
clean:
	-rm -r $(BUILD_DIR)