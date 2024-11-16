#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TEST) || defined(EMULATOR)
#include <stdio.h>
#define xprintf printf
#define xsprintf sprintf
#else
int xprintf(const char *format, ...);
int xsprintf(char *out, const char *format, ...);
#endif

#ifdef __cplusplus
}
#endif

