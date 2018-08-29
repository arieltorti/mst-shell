#include "mts.h"

int mts_launch(char **args) {
  pid_t pid;
  int status;

  pid = fork();

  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("mts");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("mts");
  } else {
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int mts_execute(char **args) {
  if (args[0] == NULL){
    return 1;
  }

  for(unsigned int i = 0; i < mts_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return mts_launch(args);
}