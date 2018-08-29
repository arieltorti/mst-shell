#include "mts.h"

void mts_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    line = mts_read_command();

    mts_printf("\n");
    args = mts_split_line(line);
    status = mts_execute(args);
    mts_print_prompt();

    free(line);
    free(args);
  } while(status);
}

int main(int argc, char **argv) {
  struct termios ttp;

  mts_init_terminal(&ttp);
  mts_clear_screen();

  mts_setup_signals();

  mts_loop();

  return EXIT_SUCCESS;
}
