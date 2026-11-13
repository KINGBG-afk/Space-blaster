#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <unistd.h>
#include <sys/ioctl.h>

unsigned short term_cols = MIN_COLS;
unsigned short term_rows = MIN_ROWS;

// gotta love how windows is trying to be different
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
char get_char(void)
{
    return _getch();
}

#else
#include <termios.h>
char get_char()
{
    struct termios oldt, newt;
    char ch;

    // get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // dissable line buffering and local echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // apply new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif

void clear_screen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void center_text(const char *s, int n)
{
    printf("%*s\n", (n + (int)strlen(s)) / 2, s);
}

int terminal_size_ok()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return 0;
    return ws.ws_col >= MIN_COLS && ws.ws_row > MIN_ROWS + STATS_ROWS;
}

int update_terminal_size(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    term_cols = ws.ws_col;
    term_rows = ws.ws_row;
    return 0;
}