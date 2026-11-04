#include "input.h"

#if defined(_WIN32) || defined(_WIN64)

#include <conio.h>

// nothing required for the 2 funcs on windows
void input_init(void)
{
}

void input_shutdown(void)
{
}

int input_poll(void)
{
    if (_kbhit())
    {
        return _getch();
    }
    return -1;
}

#else

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>

static struct termios oldt;

void input_shutdown(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void input_init(void)
{
    struct termios newt;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;

    // make sure to restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    atexit(input_shutdown);
}

int input_poll(void)
{
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    // check if input is available without blocking the program
    if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) > 0)
    {
        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            return c;
        }
    }
    return -1;
}

#endif