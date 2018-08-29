#include "mts.h"

struct termios old_tp;

void mts_init_terminal(struct termios* tp) {
  int success, errno;

  success = setupterm(NULL, 1, &errno);

  if (!success && errno < 1)
    mts_fatal("Terminal could not be setup");

  if (tcgetattr(0, tp) == -1)
    mts_fatal("Terminal could not be setup");
  old_tp = *tp;

  // No echo.
  tp->c_lflag &= ~(ECHO|ECHOK|ECHONL);
  tp->c_lflag &= ~ICANON;
  tp->c_lflag |= ISIG;

  tp->c_iflag &= ~INLCR;
  tp->c_iflag |= ICRNL;
  tp->c_iflag |= IUTF8;

  // Testing this flag, if it causes errors comment it.
  tp->c_oflag |= OPOST;

  // Set flags.
  tcsetattr(0, TCSANOW, tp);  
}

// Restore the terminal to 
// its initial state.
void mts_close_terminal() {
  tcsetattr(0, TCSANOW, &old_tp);
}