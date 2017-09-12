#!/usr/bin/make -f

NAME	= $(MCU_TARGET)-pwm
SRC	:= pwm.c
OBJ	:= $(patsubst %.c,%.o,$(SRC))

OPTS	= -Os -mmcu=$(MCU_TARGET)
CFLAGS	= -Wall -Werror -Wextra -pedantic -std=c99
LDFLAS	=
LIBS	=

CC	:= avr-gcc
OBJCOPY	:= avr-objcopy

MCU_TARGET	= atmega328p
PROGRAMMER_MCU	= m328p
PROGRAMMER	= usbasp

all: build

build: $(NAME).hex

clean:
	rm -f $(OBJ)
	rm -f $(NAME).elf
	rm -f $(NAME).hex

flash: $(NAME).hex
	avrdude -c $(PROGRAMMER) -p $(PROGRAMMER_MCU) -B 3 -U flash:w:$<

$(NAME).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OPTS) $(LDFLAGS) -o $@ $^ $(LIBS)

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.o: %.c
	$(CC) $(CFLAGS) $(OPTS) -c -o $@ $<
