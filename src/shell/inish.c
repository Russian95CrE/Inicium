/* inish.c */

#include "inish.h"
#include "../drivers/driver.h"
#include "../io/io.h"
#include "../keyboard/keyboard.h"

/*
it's hardcoded as fuck now, but keep in mind i will change that
in a future.
*/

void shell_main(void) {
    keyboard_init(); // initialize keyboard

    print("\nInish (Inicium Shell)\n");
    print("\n[shell@shell]#  ");
    
    // simple polling loop to echo keystrokes
    while (1) {
        char c = keyboard_getchar();
        if (c) {
            char buf[2] = { c, '\0' };
            print(buf);
        }
    }
}
