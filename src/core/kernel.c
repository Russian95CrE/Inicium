/* kernel.c */

#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../shell/inish.h"

// Change outw to a normal function for external linkage
void outw(unsigned short port, unsigned short val) {
    __asm__ __volatile__("outw %0, %1" : : "a"(val), "Nd"(port));
}

// BOOT.ASM points to this function as the kernel entry point
void kernel_main() {
    driver_init();
    keyboard_init();
    shell_main(); // Launch the shell

    // Fallback infinite loop
    while (1) {
        ;
    }
}