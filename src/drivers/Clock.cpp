#include <mbed.h>
#include "Clock.h"

// The us ticker is a wrapping uint32_t. We insert interrupts at
// 0, 0x40000000, 0x8000000, and 0xC0000000, rather than just 0 or just 0xFFFFFFFF because there is
// code that calls interrupts that are "very soon" immediately and we don't
// want that. Also because if we only use 0 and 0x80000000 then there is a chance it would
// be considered to be in the past and executed immediately.

class ExtendedClock : public TimerEvent
{
public:
    ExtendedClock()
    {
        // This also starts the us ticker.
        insert(0x40000000);
    }

    float read()
    {
        return read_us() / 1000000.0f;
    }

    uint64_t read_ms()
    {
        return read_us() / 1000;
    }

    uint64_t read_us()
    {
        return mTriggers * 0x40000000ull + (ticker_read(_ticker_data) & 0x3FFFFFFF);
    }

private:
    void handler() override
    {
        ++mTriggers;
        // If this is the first time we've been called (at 0x4...)
        // then mTriggers now equals 1 and we want to insert at 0x80000000.
        insert((mTriggers+1) * 0x40000000);
    }

    // The number of times the us_ticker has rolled over.
    uint32_t mTriggers = 0;
};

static ExtendedClock _GlobalClock;

// Return the number of seconds since boot.
float clock_s()
{
    return _GlobalClock.read();
}

// Return the number of milliseconds since boot.
uint64_t clock_ms()
{
    return _GlobalClock.read_ms();
}

// Return the number of microseconds since boot.
uint64_t clock_us()
{
    return _GlobalClock.read_us();
}
