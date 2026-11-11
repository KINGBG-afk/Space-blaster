#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "game.h"
#include "utils.h"

static volatile sig_atomic_t resized = 1;

static void on_resize(int sig)
{
    (void)sig;
    resized = 1;
}

int main(void)
{
    // before anything starts
    // hide the cursor
    printf("\033[?25l");
    
    struct sigaction sa = {0};
    sa.sa_handler = on_resize;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGWINCH, &sa, NULL);

    while (!terminal_size_ok())
    {
        clear_screen();
        printf("Game needs to be at least %u columns and %u rows big\n", MIN_COLS, MIN_ROWS);
        printf("Make the window bigger!\n");
        pause(); // woken by SIGWINCH
    }

    clear_screen();
    start_game();
    return 0;
}