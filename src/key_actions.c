#include "mts.h"

int mts_ctrl_l_action(char* line, unsigned int len) {
  mts_clear_screen();

  // Null terminate line in order to print it
  // This will not affect the reading of the next character.
  line[len] = '\0';
  mts_printf("%s", line);
  return 0;
}

void mts_cursor_right(unsigned int* pos){
  if (*pos > 0) {
    (*pos)--;
    mts_tputstr("le", 1);
  }
}

void mts_cursor_left(unsigned int* pos, unsigned int len){
  if (*pos < len) {
    (*pos)++;
    mts_tputstr("nd", 1);
  }
}

int mts_handle_arrow_keys(char key, struct iline* line) {
  switch(key) {
    case 'A':
      // Up Arrow
      break;
    case 'B':
      // Down Arrow
      break;
    case 'C':
      // Right Arrow
      mts_cursor_left(&line->curpos, line->len);
      break;
    case 'D':
      // Left Arrow
      mts_cursor_right(&line->curpos);
      break;
  }

  return 0;
}
