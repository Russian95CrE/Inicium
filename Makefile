CC = gcc
CFLAGS = -ffreestanding -m32
LDFLAGS = -ffreestanding -m32 -nostdlib

OBJDIR = build/obj
OUTDIR = build/out
ISODIR = isodir

all: kernel.iso

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(ISODIR)/boot/grub:
	mkdir -p $(ISODIR)/boot/grub

$(OBJDIR)/boot.o: src/boot.asm | $(OBJDIR)
	nasm -f elf32 src/boot.asm -o $(OBJDIR)/boot.o

$(OBJDIR)/kernel.o: src/kernel.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c src/kernel.c -o $(OBJDIR)/kernel.o

$(OUTDIR)/kernel.bin: $(OBJDIR)/boot.o $(OBJDIR)/kernel.o linker.ld | $(OUTDIR)
	$(CC) $(LDFLAGS) -T linker.ld $(OBJDIR)/boot.o $(OBJDIR)/kernel.o -o $(OUTDIR)/kernel.bin

kernel.iso: $(OUTDIR)/kernel.bin grub.cfg | $(ISODIR)/boot/grub
	cp $(OUTDIR)/kernel.bin $(ISODIR)/boot/kernel.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(OUTDIR)/kernel.iso $(ISODIR)

clean:
	rm -rf build isodir
