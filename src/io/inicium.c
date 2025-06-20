#include <stdint.h>

#define HPET_BASE 0xFED00000UL
#define HPET_MAIN_COUNTER (*(volatile uint64_t*) (HPET_BASE + 0xF0))
#define HPET_PERIOD (*(volatile uint32_t*) (HPET_BASE + 0x04))

void
sleep(unsigned int milliseconds) {
    uint32_t period_fs = HPET_PERIOD;
    if (period_fs != 0) {
        // HPET available
        uint32_t ticks_per_ms = 1000000U / period_fs;
        uint32_t ticks        = milliseconds * ticks_per_ms;
        uint64_t start        = HPET_MAIN_COUNTER;
        while ((uint32_t) (HPET_MAIN_COUNTER - start) < ticks) {
            // busy wait
        }
    } else {
        // Fallback: simple busy-wait loop (not accurate)
        volatile unsigned int i, j;
        for (i = 0; i < milliseconds; i++) {
            for (j = 0; j < 10000; j++) {
                __asm__ __volatile__("nop");
            }
        }
    }
}