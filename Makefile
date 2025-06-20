CC = gcc
CFLAGS = -fno-stack-protector -ffreestanding -m32
LDFLAGS = -fno-stack-protector -ffreestanding -m32 -nostdlib

OBJDIR = build/obj
OUTDIR = build/out
ISODIR = isodir

# recursively find all .c files in src and subfolders
SRCS_C = $(shell find src -name '*.c')
OBJS_C = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS_C))
# boot assembly file remains separate
BOOT_OBJ = $(OBJDIR)/boot.o

all: kernel.iso

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(ISODIR)/boot/grub:
	mkdir -p $(ISODIR)/boot/grub

$(BOOT_OBJ): src/boot.asm | $(OBJDIR)
	nasm -f elf32 src/boot.asm -o $(BOOT_OBJ)

# generic rule for C files in src/ and its subfolders
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTDIR)/kernel.bin: $(BOOT_OBJ) $(OBJS_C) linker.ld | $(OUTDIR)
	$(CC) $(LDFLAGS) -T linker.ld $(BOOT_OBJ) $(OBJS_C) -o $(OUTDIR)/kernel.bin

kernel.iso: $(OUTDIR)/kernel.bin grub.cfg | $(ISODIR)/boot/grub
	cp $(OUTDIR)/kernel.bin $(ISODIR)/boot/kernel.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(OUTDIR)/kernel.iso $(ISODIR)

clean:
	rm -rf build isodir
