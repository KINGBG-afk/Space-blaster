#ifndef UTILS_H
#define UTILS_H

// when making game loop this will be 100x40
#define MIN_ROWS 24
#define MIN_COLS 80

// externs means that it will be defined in utils.c
extern unsigned short term_cols;
extern unsigned short term_rows;

void clear_screen(void);
void center_text(const char *s, int n);
int terminal_size_ok(void); // returns 1 on success otherwise its 0
int update_terminal_size(void);
char get_char(void);

#endif