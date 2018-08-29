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

// Processes key inputs and execute any action associated with it.
// Returns 0 if key is binded to an action
// Returns 1 otherwise
int mts_process_char(char c, char* line, unsigned int len) {
  switch(c){
    case 12:
      return mts_ctrl_l_action(line, len);
  }

  return 1;
}

char *mts_read_command(void) {
  #define BUFSIZE 1024
  unsigned int bufsize = BUFSIZE;
  unsigned int len = 0;
  char* line = malloc(sizeof(char) * bufsize);
  int c;

  for(;;) {
    c = getchar();

    if ( c == EOF || c == '\n') {
      line[len] = '\0';
      return line;
    }
    
    if (mts_process_char(c, line, len) == 1) {
        line[len++] = c;
        mts_printf("%c", c);
    }

    if (len >= bufsize){
      bufsize += BUFSIZE;
      line = realloc(line, sizeof(char) * bufsize);

      if (!line)
        mts_fatal("Allocation error\n");
    }
  }
}