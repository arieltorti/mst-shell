#include "mts.h"

void mts_sigint_handler(int signal) {
  mts_close_terminal();
  write(1, "\n", 1);
  exit(1);
}
