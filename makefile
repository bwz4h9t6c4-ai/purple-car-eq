# Project Makefile for PurpleCarEQ

TARGET = PurpleCarEQ
BUILD = build
SOURCE = source

# Libraries
LIBS = -lctru -lcitro2d -lm

# Compiler
CC = arm-none-eabi-gcc
CFLAGS = -O2 -Wall -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp

# Build commands
all:
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -I/opt/devkitPro/portlibs/3ds/include -c $(SOURCE)/main.c -o $(BUILD)/main.o
	$(CC) $(CFLAGS) $(BUILD)/main.o -o $(BUILD)/$(TARGET).3dsx $(LIBS)

clean:
	rm -rf $(BUILD)
