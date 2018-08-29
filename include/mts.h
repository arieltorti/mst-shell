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

/* utils */

void mts_fatal(const char* msg, ...);
void mts_error(const char* msg, ...);

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

/* end key actions */

/* userio */

int mts_process_char(char c, char* line, unsigned int len);
char *mts_read_command(void);
char **mts_split_line(char *line);

/* end userio */

/* exec */

int mts_launch(char **args);
int mts_execute(char **args);

/* end exec */