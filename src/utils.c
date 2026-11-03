#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

unsigned short term_cols = MIN_COLS;
unsigned short term_rows = MIN_ROWS;

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void center_text(char *s, int n)
{
    printf("%*s\n", (n + (int)strlen(s)) / 2, s);
}

int terminal_size_ok()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;
    return ws.ws_col >= MIN_COLS && ws.ws_row >= MIN_ROWS;
}

int update_terminal_size(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    if (terminal_size_ok)
    {
        term_cols = ws.ws_col;
        term_rows = ws.ws_row;
        return 0;
    }

    return -1;
}