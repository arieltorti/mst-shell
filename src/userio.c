#include "mts.h"
#define MTS_TOK_BUFSIZE 64
#define MTS_TOK_DELIM " \t\r\n\a"

char **mts_split_line(char *line) {
  int bufsize = MTS_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    mts_fatal("Allocation error\n");
  }

  token = strtok(line, MTS_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += MTS_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));

      if (!tokens) {
        mts_fatal("Allocation error\n");
      }
    }

    token = strtok(NULL, MTS_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

// As we are reallocating more memory each time line.str
// is 1024 it isnt possible for memmove to overflow.
void mts_add_character(char* str, char c,
                       unsigned int pos, unsigned int len) {
  memmove(str+pos+1, str+pos, len - pos);
  str[pos] = c;
}
void mts_remove_character(struct iline* line) {
  if (line->len == 0)
    return;

  mts_tputstr("dc", 1);

  char* st = line->str + line->curpos;
  memmove(st, st+1, line->len - line->curpos + 1);
  line->len--;
  line->str[line->len] = '\0';
}

// Processes key inputs and execute any action associated with it.
// Returns 0 if key is binded to an action
// Returns 1 otherwise
int process_char(char c, struct iline* line) {
  switch(c){
    case 12:
      return mts_ctrl_l_action(line->str, line->len);
    case '\033':
      // Arrow keys
      getchar(); // Ignore [
      return mts_handle_arrow_keys(getchar(), line);
    case 127:
      mts_cursor_right(&line->curpos);
    case 126:
      mts_remove_character(line);
      return 0;
  }

  return 1;
}

char *mts_read_command(void) {
  #define BUFSIZE 1024
  unsigned int bufsize = BUFSIZE;
  struct iline line;
  int c;

  line.str = malloc(sizeof(char) * bufsize);
  line.len = 0;
  line.curpos = 0;

  for(;;) {
    c = getchar();

    if ( c == EOF || c == '\n') {
      line.str[line.len] = '\0';
      return line.str;
    }

    if (process_char(c, &line) == 1) {
      if (line.curpos != line.len) {
        mts_add_character(line.str, c, line.curpos, line.len);

        mts_tputstr("im", 1);
        mts_printf("%c", c);
        mts_tputstr("ei", 1);
      } else {
        line.str[line.len] = c;
        mts_printf("%c", c);
      }

      line.len++;
      line.curpos++;
    }

    if (line.len >= bufsize){
      bufsize += BUFSIZE;
      line.str = realloc(line.str, sizeof(char) * bufsize);

      if (!line.str)
        mts_fatal("Allocation error\n");
    }
  }
}
