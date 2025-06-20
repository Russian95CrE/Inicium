CC = gcc
CFLAGS = -fno-stack-protector -ffreestanding -m32
LDFLAGS = -fno-stack-protector -ffreestanding -m32 -nostdlib

OBJDIR = build/obj
OUTDIR = build/out
ISODIR = isodir

# recursively find all .c files in src and subfolders
SRCS_C = $(shell find src -name '*.c')
OBJS_C = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS_C))
BOOT_OBJ = $(OBJDIR)/boot.o

GRUB_CFG = $(wildcard grub.cfg)

.PHONY: all clean

all: kernel.iso
	@echo -e "\e[32mBuild complete.\e[0m"

# Directory creation (order-only prerequisites)
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(ISODIR)/boot/grub:
	mkdir -p $(ISODIR)/boot/grub

# Boot assembly
$(BOOT_OBJ): src/boot.asm | $(OBJDIR)
	nasm -f elf32 src/boot.asm -o $(BOOT_OBJ)

# vpath for C sources
vpath %.c src

# Pattern rule for C files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel binary
$(OUTDIR)/kernel.elf: $(BOOT_OBJ) $(OBJS_C) linker.ld | $(OUTDIR)
	ld -m elf_i386 -T linker.ld $(BOOT_OBJ) $(OBJS_C) -o $(OUTDIR)/kernel.elf

# ISO creation
kernel.iso: $(OUTDIR)/kernel.elf $(GRUB_CFG) | $(ISODIR)/boot/grub
	cp $(OUTDIR)/kernel.elf $(ISODIR)/boot/kernel.elf
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(OUTDIR)/kernel.iso $(ISODIR)

clean:
	$(RM) -rf build isodir
