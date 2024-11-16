#pragma once

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void clock_setup(void);
uint32_t millis(void);
void gpio_setup(void);

#ifdef __cplusplus
}
#endif
