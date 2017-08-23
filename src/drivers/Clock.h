#pragma once

#include <stdint.h>

// Return the number of seconds since boot.
float clock_s();

// Return the number of milliseconds since boot.
uint64_t clock_ms();

// Return the number of microseconds since boot.
uint64_t clock_us();
