#ifndef UTILS_H
#define UTILS_H

#define MIN_ROWS 24
#define MIN_COLS 80

extern unsigned short term_cols;
extern unsigned short term_rows;

void clear_screen(void);
void center_text(char *s, int n);
int terminal_size_ok(void); // returns 0 on success otherwise its -1
int update_terminal_size(void);

#endif