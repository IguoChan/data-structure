# define the target
TARGET = list.a
TEST_TARGET = test-list

# define the Build Directory
BUILD_DIR = build
OBJ_DIR := $(BUILD_DIR)/objs
DEP_DIR := $(BUILD_DIR)/deps

# define PATH
LOCAL_PATH = $(shell dirname "${BASH_SOURCE[0]}")

# define the sources and objects
SOURCES := $(shell find $(LOCAL_PATH)/ -name "*.c" -not -name "*_test.c")
OBJS := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(notdir $(SOURCES))))
DEPS := $(addprefix $(DEP_DIR)/, $(patsubst %.c, %.d, $(notdir $(SOURCES))))

TESTC := $(shell find $(LOCAL_PATH)/ -name "*_test.c")
TESTOBJ := $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(notdir $(TESTC))))
TESTDEPS := $(addprefix $(DEP_DIR)/, $(patsubst %.c, %.d, $(notdir $(TESTC))))

# define VPATH
VPATH = $(LOCAL_PATH)

# define the includes, compile and link flags
INCLUDES := -I$(LOCAL_PATH)
CC_FLAGS := -g $(INCLUDES)
LK_FLAGS := -lcunit -static
TEST_INC = -I/usr/local/include/CUnit
TEST_LIB = -L/usr/local/lib/

# define the compiler
CC = gcc
AR = ar 

# define the phony target
.PHONY : all clean

all: $(TARGET) $(TEST_TARGET)
# build the target 
$(TARGET): $(OBJS)
	@if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(BUILD_DIR); fi;\
	$(AR) cq $@ $^

$(TEST_TARGET): $(TESTOBJ) $(OBJS)
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
	-rm -f $(TARGET) $(TEST_TARGET)