#include <stdint.h>

#define HPET_BASE 0xFED00000UL
volatile uint64_t* const HPET_MAIN_COUNTER = (volatile uint64_t*) (HPET_BASE + 0xF0);
volatile uint32_t* const HPET_PERIOD       = (volatile uint32_t*) (HPET_BASE + 0x04);

void
sleep(unsigned int milliseconds) {
    uint32_t period_fs = *HPET_PERIOD;
    if (period_fs != 0) {
        uint64_t ticks_per_ms = 1000000000000ULL / period_fs;
        uint64_t ticks        = (uint64_t) milliseconds * ticks_per_ms;
        uint64_t start        = *HPET_MAIN_COUNTER;
        while ((*HPET_MAIN_COUNTER - start) < ticks) {
            __asm__ volatile("pause");
        }
    } else {
        // fallback simples
        volatile unsigned int i, j;
        for (i = 0; i < milliseconds; i++)
            for (j = 0; j < 10000; j++)
                __asm__ volatile("nop");
    }
}
