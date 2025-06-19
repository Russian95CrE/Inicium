/* kernel.c */

#include "../drivers/driver.h"
#include "../shell/inish.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../test_simple_c_code/hello.h"

void kernel_main() {
    clear();
    driver_init();
    keyboard_init();
    hello();
    shell_main(); // Launch the shell

    // Fallback infinite loop
    while (1) {
        ;
    }
}