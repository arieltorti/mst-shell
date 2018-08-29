#include "mts.h"

int mts_output_char(int c){
  return write(1, &c, 1);
}

// Based on linux Kernel outputError
static void output(const char* format, va_list ap, int fd) {
  #define BUFSIZE 1024
  char msg[BUFSIZE], output[BUFSIZE];

  vsnprintf(msg, BUFSIZE, format, ap);
  if (fd == 2){
    snprintf(output, BUFSIZE, "mts: %s", msg);
    tputs(output, fd, mts_output_char);
  } else {
    tputs(msg, fd, mts_output_char);
  }
}

void mts_fatal(const char* format, ...) {
  va_list ap;

  va_start(ap, format);
  mts_error(format, ap);
  va_end(ap);

  exit(EXIT_FAILURE);
}

void mts_error(const char* format, ...) {
  va_list ap;

  va_start(ap, format);
  output(format, ap, 2);
  va_end(ap);
}

void mts_printf(const char* format, ...){
  va_list ap;

  va_start(ap, format);
  output(format, ap, 1);
  va_end(ap);
}

void mts_print_prompt() {
  mts_printf("%s> ", getenv("USER"));
}

void mts_clear_screen() {
  char *str;

  str = tgetstr("cl", NULL);
  tputs(str, 1, mts_output_char);

  mts_print_prompt();
}