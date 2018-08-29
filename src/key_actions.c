#include "mts.h"

int mts_ctrl_l_action(char* line, unsigned int len) {
    mts_clear_screen();

    // Null terminate line in order to print it
    // This will not affect the reading of the next character.
    line[len] = '\0';
    mts_printf("%s", line);
    return 0;
}