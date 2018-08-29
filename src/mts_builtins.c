#include "mts.h"

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &mts_cd,
  &mts_help,
  &mts_exit
};

unsigned int mts_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int mts_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "mts: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("mts");
    }
  }
  return 1;
}

int mts_help(char **args) {
  printf("Ariel Torti's LSH\n");
  printf("Type program names and arguments, then hit enter.\n");
  printf("The following are built in:\n");

  for (unsigned int i = 0; i < mts_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int mts_exit(char **args){
  return 0;
}
