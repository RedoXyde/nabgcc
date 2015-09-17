# The name of the target file
TARGET = testVM

# User options
OPTIONS += -DDEBUG
OPTIONS += -DDEBUG_WIFI
OPTIONS += -DDEBUG_USB
OPTIONS += -D_NAB_SIM
OPTIONS += -DDEBUG_VM

# C Files to compile (take all)

C_FILES  = src/bc.c testvm.c
C_FILES += $(wildcard src/vm/*.c)
C_FILES += $(wildcard src/net/*.c)
C_FILES += $(wildcard stubs/**/*.c)
# C_FILES += $(wildcard ../sys/src/*.c)
# AS_FILES = $(wildcard ../sys/asm/*.s)

# Compiler options
CFLAGS += -O0
CFLAGS += -g
CFLAGS += -Wall -Wextra -Wno-unused-parameter -Wpointer-arith
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -fno-exceptions -fno-delete-null-pointer-checks
CFLAGS +=  -MMD
CFLAGS += $(OPTIONS)
CFLAGS += -I../inc/
CFLAGS += -I../sys/inc

# Linker options
LD_FLAGS =
#~ LDFLAGS +=  -Wl,--gc-sections
#~ LDFLAGS += -Wl,-s
LDFLAGS += -Wl,-Map,obj/$(TARGET).map
LDFLAGS += -Wa,-adhln=obj/$(TARGET).lst

# Additional libraries
LIBS = -lm
#-lc_nano -lnosys

# Compiler toolchain
CC = gcc
OBJCOPY = objcopy
SIZE = size
NM = nm
DUMP = objdump
DEBUG = gdb

OBJS = $(C_FILES:%.c=obj/%.o)
OBJS += $(AS_FILES:%.s=obj/%.o)

all: elf

elf: $(TARGET)
	$(SIZE) $<

dis: bin/$(TARGET).elf
	$(NM) -lS $< > obj/$(TARGET).sym
	$(DUMP) -d $< > obj/$(TARGET).dis

obj/%.o : %.c
	@test -d $(@D) || mkdir -pm 775 $(@D)
	@test -d obj/lst/$(<D) || mkdir -pm 775 obj/lst/$(<D)
	$(CC) -c $(CFLAGS) -Wa,-adhln=obj/lst/$<.lst $< -o $@  $(LIBS)

obj/%.o : %.s
	@test -d $(@D) || mkdir -pm 775 $(@D)
	@test -d obj/lst/$(<D) || mkdir -pm 775 obj/lst/$(<D)
	$(CC) -o $@ $(CFLAGS) -Wa,-adhln=obj/lst/$<.lst -x assembler-with-cpp -c $<

# compiler generated dependency info
-include $(OBJS:.o=.d)

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@rm -f $(TARGET)
	@rm -Rf obj/

debug: $(TARGET)
	$(DEBUG) $< < gdb_load

.PHONY: clean debug elf
