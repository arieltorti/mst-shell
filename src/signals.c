#include "mts.h"
#include "mts_handlers.h"

void mts_setup_signals() {
    signal(SIGINT, mts_sigint_handler);
}
