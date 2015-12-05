BIN=ds1821demo
STLINK=/usr/local/bin

TOOLS_PATH=/usr
TOOLS_PREFIX=arm-none-eabi-
TOOLS_VERSION=4.9.3

STM_COMMON=../../STM32F10x_StdPeriph_Lib_V3.5.0
CMSIS=$(STM_COMMON)/Libraries/CMSIS/CM3

CFLAGS=-c -mcpu=cortex-m3 -mthumb -Wall -O0 -mapcs-frame -D__thumb2__=1 
CFLAGS+=-msoft-float -gdwarf-2 -mno-sched-prolog -fno-hosted -mtune=cortex-m3 
CFLAGS+=-march=armv7-m -mfix-cortex-m3-ldrd -ffunction-sections -fdata-sections 
CFLAGS+=-I$(CMSIS)/CoreSupport -I./stm32_lib -I.
ASFLAGS=-mcpu=cortex-m3 -I$(CMSIS)/CoreSupport -I./stm32_lib -gdwarf-2 -gdwarf-2
LDFLAGS=-static -mcpu=cortex-m3 -mthumb -mthumb-interwork -Wl,--start-group 
LDFLAGS+=-L$(TOOLS_PATH)/lib/gcc/arm-none-eabi/$(TOOLS_VERSION)/thumb2 
LDFLAGS+=-L$(TOOLS_PATH)/arm-none-eabi/lib/thumb2 -specs=nosys.specs -lc -lg -lstdc++ -lsupc++ -lgcc -lm 
#LDFLAGS+=--section-start=.text=0x8000000
LDFLAGS+=-Wl,--end-group -Xlinker -Map -Xlinker $(BIN).map -Xlinker 
LDFLAGS+=-T ./stm32f100rb_flash.ld -o $(BIN).elf

CC=$(TOOLS_PATH)/bin/$(TOOLS_PREFIX)gcc-$(TOOLS_VERSION)
AS=$(TOOLS_PATH)/bin/$(TOOLS_PREFIX)as
SIZE=$(TOOLS_PATH)/bin/$(TOOLS_PREFIX)size
OBJCOPY=$(TOOLS_PATH)/bin/$(TOOLS_PREFIX)objcopy

CMSISSRC=$(CMSIS)/CoreSupport/core_cm3.c
STM32_LIBSRC=./stm32_lib/system_stm32f10x.c 
STM32_LIBSRC+=

SRC=main.c
SRC+=delay.c stm32f10x_onewire.c ds1821.c

OBJ=main.o
OBJ+=delay.o stm32f10x_onewire.o ds1821.o
OBJ+=core_cm3.o system_stm32f10x.o startup_stm32f10x_md_vl.o
OBJ+=

all: ccmsis cstm32_lib cc ldall
	$(SIZE) -B $(BIN).elf
	$(OBJCOPY) -O ihex $(BIN).elf $(BIN).hex
	$(OBJCOPY) -O binary $(BIN).elf $(BIN).bin

ccmsis: $(CMSISSRC)
	$(CC) $(CFLAGS) $(CMSISSRC)

cstm32_lib: $(STM32_LIBSRC)
	$(CC) $(CFLAGS) $(STM32_LIBSRC)
	$(AS) $(ASFLAGS) $(CMSIS)/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md_vl.s -o startup_stm32f10x_md_vl.o

cc: $(SRC)
	$(CC) $(CFLAGS) $(SRC)

ldall:
	$(CC) $(OBJ) $(LDFLAGS)

.PHONY: clean load

clean:
	rm -f 	$(OBJ) \
		$(BIN).map \
		$(BIN).elf \
		$(BIN).hex \
		$(BIN).bin

# Flash the STM32F10x
burn: $(BIN).bin
	$(STLINK)/st-flash write $(BIN).bin 0x8000000
