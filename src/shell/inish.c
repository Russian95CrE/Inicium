/* inish.c */

#include "inish.h"
#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "commands.h"

/*
It is hardcoded as fuck now, but keep in mind i will change that
in a future.
*/

void shell_main(void) {
    clear();
    keyboard_init(); // initialize keyboard

    printf("\nInish (Inicium Shell)\n");

    char cmd_buf[256];
    int  cmd_len = 0;

    while (1) {
        printf("\n[shell@shell]# ");
        cmd_len    = 0;
        cmd_buf[0] = '\0';

        while (1) {
            char c = keyboard_getchar();
            if (c) {
                if (c == '\n') {
                    printf("\n");
                    cmd_buf[cmd_len] = '\0';
                    // Simple command handling
                    if (cmd_len > 0) {
                        int handled = 0;
                        if (strcmp(cmd_buf, "clear") == 0) {
                            clear();
                            handled = 1;
                        }
                        if (strcmp(cmd_buf, "poweroff") == 0) {
                            poweroff();
                            handled = 1;
                        }
                        if (!handled && strcmp(cmd_buf, "poweroff") != 0) {
                            printf("Command not found: %s\n", cmd_buf);
                        }
                    }
                    break; // Print prompt again
                } else if (c == '\b') {
                    if (cmd_len > 0) {
                        cmd_len--;
                        printf("\b \b"); // Erase character from screen
                    }
                } else if (cmd_len < (int)sizeof(cmd_buf) - 1) {
                    cmd_buf[cmd_len++] = c;
                    printf("%c", c);
                }
            }
        }
    }
}
