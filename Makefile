###############################################################################
# File: Makefile
# Description: CDFJ Test Makefile
# (C) Copyright 2017 - Chris Walton, Fred Quimby, Darrell Spice Jr
# Modifications for Wen Hop by Andrew Davie
# used, modified, and distriuted with permission (February 2023)
#########∫######################################################################

PROJECT=WenHop
DASM_TO_C=defines_from_dasm_for_c.h

# If desired, the following color values can be changed.
# 30=black  31=red      32=green    33=yellow
# 34=blue   35=purple   36=cyan     37=white
INFO_COLOR='\033[1;34m'     #default 34=blue
OPTION_COLOR='\033[0;32m'   #default 32=green
PROMPT_COLOR='\033[0;37m'   #default 37=white
ERROR_COLOR='\033[0;31m'    #defualt 31=red

# do not change this
DEFAULT_COLOR='\033[0m'

# Tool names
#TOOLCHAIN=arm-elf
TOOLCHAIN= ~/Documents/software/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi
TOOLPATH = ./tools

#TOOLCHAIN=arm-eabi
CC=$(TOOLCHAIN)-gcc
AS=$(TOOLCHAIN)-as
LD=$(TOOLCHAIN)-ld
OBJCOPY=$(TOOLCHAIN)-objcopy
SIZE=$(TOOLCHAIN)-size
DASM=$(TOOLPATH)/dasm

# Dirs
BASE = main
SRC = $(BASE)/custom
BIN = $(BASE)/bin

SRCS =  characterset.c	joystick.c	random.c	swipeCircle.c \
		animations.c	colour.c	main.c		mellon.c \
		atarivox.c	decodecaves.c	menu.c		score.c \
		attribute.c	drawplayer.c	scroll.c \
		cavedata.c	drawscreen.c		sound.c player.c wyrm.c


# C Compiler flags
OPTIMIZATION =  -Os
CFLAGS = -g3 -gdwarf-4 -gstrict-dwarf -mcpu=arm7tdmi -march=armv4t -mthumb # -mthumb-interwork
CFLAGS += -Wall -Wextra -Wunused-macros -ffunction-sections # -save-temps #-mlong-calls
CFLAGS += $(OPTIMIZATION)
CFLAGS += -Wl,--print-memory-usage,--build-id=none -flto -mno-thumb-interwork -fextended-identifiers


# Search path
VPATH += $(BASE):$(SRC)
SERIAL_DATE := $(shell date +"const int serialNumberDate = %y%m%d;")
SERIAL_TIME := $(shell date +"const int serialNumberime = %H%M%S;")
TARGET := $(shell date +"WenHop_%Y%m%d@%H:%M:%S" | tr ' :' '__')

# # srcs = $(wildcard *.c)
# # objs = $(srcs:.c=.o)
# # deps = $(srcs:.c=.d)
# asmSrcs = $(wildcard *.asm) macro.h vcs.h cdfj.h


# export FOO='hello'

# Default target
default: armcode
	# echo $(FOO)
	@#sleep 20
	@#open -a /Applications/Stella.app ./$(PROJECT).bin
	@zsh -c "nohup ../Gopher2600/gopher2600_darwin_arm64 -right savekey $(SHOWFPS) ./$(PROJECT).bin &"
#	zsh -c "sudo nohup nice -20 ../Gopher2600/gopher2600_darwin_amd64 -showfps ./WenHop.bin &"
	@sleep 1

gfx:
	(cd gfx & make)



.PHONY: killEmulator
killEmulator:
	@killall gopher2600_darwin_arm64 || true > silent
	@#osascript -e 'quit app "Stella"'

armcode_defines: gfx $(asmSrcs)
	#echo $(SERIAL_DATE) > main/serial_date.txt
	#echo $(SERIAL_TIME) > main/serial_time.txt
	@printf $(INFO_COLOR)
	@echo "Step 1/3 - Create $(DASM_TO_C)"
	@printf $(OPTION_COLOR)
	$(DASM) $(PROJECT).asm -p100 -f3 -v0 -s$(PROJECT).sym -l$(PROJECT).lst -o$(PROJECT).bin
	@echo "// Do not change this file. It is auto-generated during the make process" > main/$(DASM_TO_C)
	awk '$$0 ~ /^_/ {printf "#define %-25s 0x%s\n", $$1, $$2}' $(PROJECT).sym >> main/$(DASM_TO_C)



#	awk 'FNR==NR {exclude[$$0]; next} {found=0; for (str in exclude) if (index($$0, str)==1) found=1} !found' excluded_strings.txt main/$(DASM_TO_C)x >> main/$(DASM_TO_C)


#	awk 'FNR==NR {exclude[$$0]; next} {found=0; for (str in exclude) if (index($$0, str) != 0) found=1} !found' excluded_strings.txt main/$(DASM_TO_C)x >> main/$(DASM_TO_C)


	@printf $(INFO_COLOR)
	@echo "Step 2/3 - Create ARM BIN"
	@printf $(OPTION_COLOR)

armcode_atari:
	$(DASM) $(PROJECT).asm -p100 -f3 -v0 -s$(PROJECT).sym -l$(PROJECT).lst -o$(PROJECT).bin
	@cp $(PROJECT).bin ROMs/$(TARGET).bin

armcode_list:

	@printf $(INFO_COLOR)
	@echo "Step 3/3 - Create BIN"
	@printf $(OPTION_COLOR)
	$(DASM) $(PROJECT).asm -p100 -f3 -v0 -o$(PROJECT).bin -l$(PROJECT).lst -s$(PROJECT).sym
	@printf $(DEFAULT_COLOR)

armcode: killEmulator armcode_defines armcode_arm armcode_list armcode_atari


gfx: tools/logo.py copyright.asm

copyright.asm: gfx/copyright.png
	@echo "processing copyright image"
	python3 $(TOOLPATH)/logo.py gfx/copyright.png

#flash:
#	lpc21isp -bin -wipe -verify -control -controlswap $(PROJECT).bin /dev/ttyUSB0 38400 10000

############################# CUSTOM C ##############################

CUSTOMNAME = armcode
CUSTOMELF = $(BIN)/$(CUSTOMNAME).elf
CUSTOMBIN = $(BIN)/$(CUSTOMNAME).bin
CUSTOMMAP = $(BIN)/$(CUSTOMNAME).map
CUSTOMLST = $(BIN)/$(CUSTOMNAME).lst
CUSTOMLINK = $(SRC)/custom.boot.lds
CUSTOMOBJS = main.o sound.o custom.o attribute.o random.o \
	decodecaves.o characterset.o mellon.o cavedata.o drawplayer.o \
	player.o drawscreen.o colour.o swipeCircle.o score.o \
	scroll.o animations.o menu.o atarivox.o joystick.o wyrm.o particle.o
CUSTOMDEPENDS = sound.h main.h attribute.h wyrm.h

CUSTOMTARGETS = $(CUSTOMELF) $(CUSTOMBIN)



#main.o : atarivox.c main.c $(DASM_TO_C)

alphanumeric.o: bitpatterns.h

#WenHop.asm : copyright.asm menuKernel.asm normalKernel.asm titleData.asm vcs.h macro.h cdfj.h atarivox/speakjet.h atarivox/speechData.asm

armcode_arm: $(CUSTOMTARGETS)
	@ls -l $(CUSTOMBIN)

$(CUSTOMELF): $(asmSrcs) $(CUSTOMOBJS) $(CUSTOMDEPENDS) Makefile
	$(CC) $(CFLAGS) -o $(CUSTOMELF) $(CUSTOMOBJS) -T $(CUSTOMLINK) -nostartfiles -Wl,-Map=$(CUSTOMMAP)
	$(TOOLCHAIN)-objdump -Sdrl $(CUSTOMELF) > $(BIN)/$(CUSTOMNAME).obj
#	,--gc-sections
$(CUSTOMBIN): $(CUSTOMELF)
	$(OBJCOPY) -O binary -S $(CUSTOMELF) $(CUSTOMBIN)
	$(SIZE) $(CUSTOMOBJS) $(CUSTOMELF)

#depend:
#	cd main && makedepend -- $(CFLAGS) -- $(SRCS)
#
#include main/Makefile


############################# CLEAN PROJECT ###################################

clean:
	rm -f *.o *.i *.s $(BIN)/*.* $(PROJECT).bin $(PROJECT).lst $(PROJECT).sym

# DO NOT DELETE

characterset.o: main/main.h main/defines_from_dasm_for_c.h main/bitpatterns.h main/characterset.h
characterset.o: main/scroll.h
joystick.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/joystick.h
joystick.o: main/defines.h main/menu.h main/swipeCircle.h
random.o: main/random.h
swipeCircle.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/sound.h
swipeCircle.o: main/swipeCircle.h
animations.o: main/main.h main/defines_from_dasm_for_c.h main/animations.h main/attribute.h
animations.o: main/random.h
colour.o: main/defines.h main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h
colour.o: main/cavedata.h main/colour.h main/score.h main/scroll.h
main.o: main/defines_cdfj.h main/defines.h main/main.h main/defines_from_dasm_for_c.h
main.o: main/animations.h main/attribute.h main/atarivox.h main/bitpatterns.h main/cavedata.h
main.o: main/characterset.h main/colour.h main/decodecaves.h main/drawplayer.h main/drawscreen.h
main.o: main/joystick.h main/menu.h main/player.h main/random.h main/mellon.h main/score.h
main.o: main/scroll.h main/sound.h main/swipeCircle.h
mellon.o: main/defines_cdfj.h main/defines.h main/main.h main/defines_from_dasm_for_c.h
mellon.o: main/animations.h main/attribute.h main/atarivox.h main/player.h main/mellon.h main/random.h
mellon.o: main/score.h main/sound.h
atarivox.o: main/defines_from_dasm_for_c.h main/defines_cdfj.h main/main.h
decodecaves.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/decodecaves.h
decodecaves.o: main/attribute.h main/characterset.h main/random.h main/mellon.h
decodecaves.o: main/scroll.h
menu.o: main/defines.h main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/menu.h
menu.o: main/atarivox.h main/bitpatterns.h main/cavedata.h main/colour.h main/joystick.h
menu.o: main/player.h main/random.h main/sound.h
score.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h
score.o: main/bitpatterns.h main/mellon.h main/score.h main/sound.h main/swipeCircle.h
attribute.o: main/attribute.h main/main.h main/defines_from_dasm_for_c.h
drawplayer.o: main/defines_cdfj.h main/defines.h main/main.h main/defines_from_dasm_for_c.h
drawplayer.o: main/drawplayer.h main/swipeCircle.h main/colour.h main/attribute.h main/player.h
drawplayer.o: main/mellon.h main/scroll.h
scroll.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/player.h main/scroll.h
scroll.o: main/mellon.h
cavedata.o: main/main.h main/defines_from_dasm_for_c.h main/cavedata.h main/attribute.h
drawscreen.o: main/defines.h main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h
drawscreen.o: main/animations.h main/attribute.h main/bitpatterns.h main/characterset.h
drawscreen.o: main/drawplayer.h main/drawscreen.h main/menu.h main/random.h main/scroll.h main/sound.h
sound.o: main/defines_cdfj.h main/main.h main/defines_from_dasm_for_c.h main/sound.h main/random.h
player.o: main/defines_from_dasm_for_c.h main/main.h main/player.h main/atarivox.h main/bitpatterns.h
player.o: main/mellon.h
wyrm.o: main/wyrm.h
particle.o: main/particle.h main/defines_cdfj.h main/defines_from_dasm_for_c.h
