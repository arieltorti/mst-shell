#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>

int mts_cd(char **args);
int mts_help(char **args);
int mts_exit(char **args);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

unsigned int mts_num_builtins();

struct iline {
  char* str;
  unsigned int len;
  unsigned int curpos;
};

/* utils */

void mts_fatal(const char* msg, ...);
void mts_error(const char* msg, ...);
void mts_tputstr(const char* str, unsigned int affcnt);

/* end utils */

void mts_clear_screen(void);
int mts_output_char(int c);

/* tty */

void mts_init_terminal(struct termios* tp);
void mts_close_terminal(void);
void mts_printf(const char* format, ...);
void mts_print_prompt(void);

/* end tty */

/* signals */

void mts_setup_signals(void);

/* end signals */

/* key actions */

int mts_ctrl_l_action(char* line, unsigned int len);
int mts_handle_arrow_keys(char key, struct iline* line);
void mts_cursor_right(unsigned int* pos);

/* end key actions */

/* userio */

char *mts_read_command(void);
char **mts_split_line(char *line);

/* end userio */

/* exec */

int mts_launch(char **args);
int mts_execute(char **args);

/* end exec */
