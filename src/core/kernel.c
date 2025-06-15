/* kernel.c */

#include "../drivers/driver.h"
#include "../shell/inish.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"

void kernel_main() {
    clear();
    driver_init();
    keyboard_init();
    shell_main(); // launch the shell

    // fallback infinite loop
    while (1) {
        ;
    }
}