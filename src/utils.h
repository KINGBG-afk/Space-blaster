#ifndef UTILS_H
#define UTILS_H

// min to display the game screen
#define MIN_ROWS 26
#define MIN_COLS 84

#define STATS_ROWS 3

// externs means that it will be defined in utils.c
extern unsigned short term_cols;
extern unsigned short term_rows;

void clear_screen(void);
void center_text(const char *s, int n);
int terminal_size_ok(void); // returns 0 on success otherwise its 1
int update_terminal_size(void);
char get_char(void);

#endif