#include "timer.h"

// again windows had to be different hehe
#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

void limit_fps(int fps)
{
    static LARGE_INTEGER frequency;
    static int initialized = 0;

    if (!initialized)
    {
        QueryPerformanceFrequency(&frequency);
        initialized = 1;
    }

    static LARGE_INTEGER previous = {0};
    LARGE_INTEGER now;

    QueryPerformanceCounter(&now);
    if (previous.QuadPart == 0)
    {
        previous = now;
        return;
    }

    double target = 1.0 / fps;
    double elapsed = (double)(now.QuadPart - previous.QuarPart) / frequency.QuadPart;

    if (elapsed < target)
    {
        DWORD miliseconds = (DWORD)((target - elapsed) * 1000.0);

        if (miliseconds > 0)
        {
            Sleep(miliseconds);
        }

        previous = now;
    }
}

#else
#include <time.h>

void limit_fps(int fps)
{
    static struct timespec previous = {0};
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    if (previous.tv_sec == 0 && previous.tv_nsec == 0)
    {
        previous = now;
        return;
    }

    double elapsed = (now.tv_sec - previous.tv_sec) + (now.tv_nsec - previous.tv_nsec) / 1e9;
    double remaining = (1.0 / fps) - elapsed;

    if (remaining > 0)
    {
        struct timespec sleep_time = {
            .tv_sec = (time_t)remaining,
            .tv_nsec = (long)((remaining - (time_t)remaining) * 1e9)};
        nanosleep(&sleep_time, NULL);
    }
    previous = now;
}

#endif