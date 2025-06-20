/* kernel.c */

#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../shell/inish.h"

void kernel_main() {
    driver_init();
    keyboard_init();
    shell_main(); // Launch the shell

    // Fallback infinite loop
    while (1) {
        ;
    }
}