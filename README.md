# Inicium

Inicium is a simple kernel written in C and x86 assembly.

## Features

- VGA text mode output (80x25)
- Basic keyboard input (US layout)
- Minimal shell interface
- Modular driver structure

## Directory Structure

- `src/core/` - Kernel entry point and core logic
- `src/drivers/` - Hardware drivers (video, etc.)
- `src/io/` - Input/output utilities
- `src/keyboard/` - Keyboard driver
- `src/shell/` - Shell implementation

## Building

You need an i386-elf cross-compiler and NASM. If you don't have them, install them first.

```sh
./build.sh
```

## Running

Run with QEMU or real hardware, if you hate yourself.

```sh
qemu-system-i386 -kernel build/inicium.bin
```

## Notes

- Please, for the love of god, don't fucking use this as your daily driver.
- This is a minimal, hardcoded kernel for learning and experimentation.
- Only basic VGA and keyboard support are implemented.
- Contributions are welcome, but keep it simple and readable.
- If you break it, you get to keep both pieces.