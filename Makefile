CROSS_COMPILE =/home/gaochao/gaochao/MipsTools-Linux/bin/mips-sde-elf-
CC =       $(CROSS_COMPILE)gcc
LD =       $(CROSS_COMPILE)ld
OBJCOPY =  $(CROSS_COMPILE)objcopy
OBJDUMP =  $(CROSS_COMPILE)objdump

INCLDIR = include
CFLAGS = -march=4kc -O0 -G 0 -mno-abicalls -fno-pic -I ${INCLDIR} -Wall

kernel_dir := kernel
lib_dir := lib
arch_dir := arch


%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $*.o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o


.PHONY : all clean

all : zos.elf

#your code here, finish dependency of zos.elf
zos.elf : $(arch_dir)/start.o \
	$(arch_dir)/uart8250.o \
	$(lib_dir)/print.o \
	$(lib_dir)/printk.o \
	$(kernel_dir)/main.o

#	$(LD) -o zos.elf -T zos.lds $(LOADADDR) $^
	$(LD) -o zos.elf -T zos.lds $^


clean:
	rm -f ./*/*~ ./*/*.o zos.elf ./*~
