# define the target
TARGET = list.a
TEST_TARGET = test-list

# define the Build Directory
BUILD_DIR = build
OBJ_DIR := $(BUILD_DIR)/objs
DEP_DIR := $(BUILD_DIR)/deps

# define PATH
LOCAL_PATH = $(shell dirname "${BASH_SOURCE[0]}")
$(info ${LOCAL_PATH})

# define the sources and objects
SOURCES := $(shell find $(LOCAL_PATH)/ -name "*.c" -not -name "*_test.c")
ALL_SOURCES := $(shell find $(LOCAL_PATH)/ -name "*.c")
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(notdir $(SOURCES))))
DEPS := $(addprefix $(DEP_DIR)/, $(patsubst %.c, %.d, $(notdir $(SOURCES))))

# define VPATH
VPATH = $(LOCAL_PATH)

# define the includes, compile and link flags
INCLUDES := -I$(LOCAL_PATH)
CC_FLAGS := -g $(INCLUDES)
TEST_INC = -I/usr/local/include/CUnit
TEST_LIB = -L/usr/local/lib/

# define the compiler
CC = gcc
AR = ar 

# define the phony target
.PHONY : test clean

# build the target 
$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi;\
	$(AR) cq $@ $^

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

test: $(TEST_TARGET)
$(TEST_TARGET): $(ALL_SOURCES)
	$(CC) -o $@ $^ -lcunit -static

# clean all products
clean:
	-rm -r $(BUILD_DIR)