# BUILDFLAGS:
# -DAVR_AT90S8515	or
# -DAVR_ATMEGA163
# -DX...	setting to a coded crystal frequency
# -DLOWON	active low segment drive
# -DSIXSEGMENT	six segment display
# -DRAISEDZERO	upper loop used for 0 in six segment mode
# -DDS3231	use DS3231 RTC
#
# Example:
# BUILDFLAGS=-DAVR_AT90S8515 -DLOWON
#
MCU?=AT90S8515
CSRCS=clock.c ds3231.c i2c.c
BUILDFLAGS=-DLOWON -DRAISEDZERO # -DDS3231

ifeq "$(MCU)" "AT90S8515"
CSRCS+=at90s8515.c
BUILDFLAGS+=-DAT90S8515 -DX8_000_000 -DSIXSEGMENT 
# CRTs are inside the avr-gcc distribution
CRT=crtat90s8515.o 
MCUOPT=-mmcu=avr2
endif

ifeq "$(MCU)" "ATMEGA163"
CSRCS+=atmega163.c
BUILDFLAGS+=-DATMEGA163 -DX4_000_000
# CRTs are inside the avr-gcc distribution
CRT=crtatmega163.o 
MCUOPT=-mmcu=avr5
endif

#Compiler
CC=avr-gcc
DEBUG=
CFLAGS=$(MCUOPT) -Wall $(DEBUG) -Os $(BUILDFLAGS) -DBUILDFLAGS="$(BUILDFLAGS)"
INCLUDES=-Ipt-1.4
OBJS=$(CSRCS:.c=.o)
LFLAGS=$(MCUOPT) -Wl,-Map,$(@:.elf=.map)
AVRSIZE=avr-size
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump

clock.bin:	clock.hex

clock.elf:	$(OBJS)
	$(CC) $(LFLAGS) $(CRT) $(OBJS) -o $@
	$(AVRSIZE) -C $@

%.s:		%.c %.h
	$(CC) $(CFLAGS) $(INCLUDES) -S $<

%.o:		%.c %.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

%.hex:		%.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $(<:.elf=.hex)

%.lst:		%.elf
	$(OBJDUMP) -h -S $< > $(<:.elf=.lst)

%.bin:		%.hex
	hex2bin $<

clean:
	rm -f *.s $(OBJS) *.elf *.hex *.lst *.map
