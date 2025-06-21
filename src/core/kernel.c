#include <stdint.h>
#include <stdbool.h>
#include "../drivers/driver.h"
#include "../io/stdio.h"
#include "../keyboard/keyboard.h"
#include "../drivers/video/video.h"
#include "../shell/commands.h"
#include "../shell/inish.h"
#include "../serial/serial.h"
#include "multiboot.h"
#include "../io/inicium.h"

int
kernel_panic(const char* msg, int errorCode) {
    (void) msg;
    (void) errorCode;
    // Optionally print error or halt
    return -1;
}

void
kernel_main(void* mb_info) {
    if (mb_info == NULL) {
        kernel_panic("Invalid multiboot info detected!", 1);
        while (1)
            __asm__("hlt");
    }
    (void) mb_info;
    driver_init();
    keyboard_init();
    shell_main();
    while (1)
        __asm__("hlt");
}
