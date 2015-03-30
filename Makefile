# The name of the target file
TARGET = Nab

# User options
OPTIONS =

# C Files to compile (take all)
C_FILES = $(wildcard src/*.c)
C_FILES += $(wildcard sys/src/*.c)

AS_FILES = $(wildcard sys/asm/*.s)

# Compiler options
CFLAGS =  -DVREAL
CFLAGS += -Wall -Os -g
#~ CFLAGS += -mthumb
#~ CFLAGS += -mthumb-interwork
CFLAGS += -Wextra -Wno-unused-parameter -Wpointer-arith
CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -fno-exceptions -fno-delete-null-pointer-checks
CFLAGS += -mcpu=arm7tdmi -nostdlib -MMD
CFLAGS += $(OPTIONS)
CFLAGS += -Iinc/ -Isys/inc

LDSCRIPT = sys/ml67q4051.ld

# Linker options
LD_FLAGS =
#~ LDFLAGS +=  -Wl,--gc-sections
#~ LDFLAGS += -Wl,-s
LDFLAGS += -Wl,-Map,obj/$(TARGET).map
LDFLAGS += -nostartfiles
LDFLAGS += -mcpu=arm7tdmi -T$(LDSCRIPT)

# Additional libraries
LIBS = -lm -lc_nano -lnosys

# Compiler toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
PROGRAM = arm-none-eabi-gdb

OBJS = $(C_FILES:%.c=obj/%.o)
OBJS += $(AS_FILES:%.s=obj/%.o)

all: elf hex bin

elf: $(TARGET).elf
	$(SIZE) $<

hex: $(TARGET).hex

bin: $(TARGET).bin

obj/%.o : %.c
	@test -d obj || mkdir  -pm 775 obj
  @test -d obj/lst || mkdir  -pm 775 obj/lst
	@test -d $(@D) || mkdir -pm 775 $(@D)
	$(CC) -c $(CFLAGS) -Wa,-adhln=obj/lst/$<.lst $< -o $@  $(LIBS)

obj/%.o : %.s
	@test -d obj || mkdir  -pm 775 obj
  @test -d obj/lst || mkdir  -pm 775 obj/lst
	@test -d $(@D) || mkdir -pm 775 $(@D)
	$(CC) -o $@ $(CFLAGS) -Wa,-adhln=obj/lst/$<.lst -x assembler-with-cpp -c $<

# compiler generated dependency info
-include $(OBJS:.o=.d)

%.elf : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(TARGET).elf $(TARGET).hex
	rm -Rf obj/

program: $(TARGET).elf
	$(PROGRAM) $< < gdb_load

.PHONY: clean program elf hex bin
