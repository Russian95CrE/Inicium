CC = gcc

COMMON_CFLAGS  = -fno-stack-protector -ffreestanding -m64 -Wall -Wextra -Wpedantic -Wconversion -Werror
COMMON_LDFLAGS = -fno-stack-protector -ffreestanding -m64 -nostdlib

MODE ?= Release

ifeq ($(MODE), Debug)
    CFLAGS  = $(COMMON_CFLAGS) -Og -g1
    LDFLAGS = $(COMMON_LDFLAGS)
else ifeq ($(MODE), Release)
    CFLAGS  = $(COMMON_CFLAGS) -O3 -march=native -mtune=native -flto -fno-omit-frame-pointer
    LDFLAGS = $(COMMON_LDFLAGS)
else
    $(error INVALID MODE: use Debug or Release)
endif

OBJDIR = build/obj
OUTDIR = build/out
ISODIR = isodir

SRCS_C   = $(shell find src -name '*.c')
OBJS_C   = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS_C))
BOOT_OBJ = $(OBJDIR)/boot.o
GRUB_CFG = $(wildcard grub.cfg)

.PHONY: all clean

all: kernel.iso
	@echo -e "\e[33mBuilding in $(MODE) mode...\e[0m"
	@echo -e "\e[32mBuild complete.\e[0m"

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(ISODIR)/boot/grub:
	mkdir -p $(ISODIR)/boot/grub

$(BOOT_OBJ): src/boot.asm | $(OBJDIR)
	nasm -f elf64 $< -o $@

vpath %.c src

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/kernel.elf: $(BOOT_OBJ) $(OBJS_C) linker.ld | $(OUTDIR)
	$(CC) $(LDFLAGS) -T linker.ld $(BOOT_OBJ) $(OBJS_C) -o $@

kernel.iso: $(OUTDIR)/kernel.elf $(GRUB_CFG) | $(ISODIR)/boot/grub
	cp $(OUTDIR)/kernel.elf $(ISODIR)/boot/kernel.elf
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(OUTDIR)/kernel.iso $(ISODIR)

clean:
	$(RM) -rf build isodir
