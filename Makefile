IDIR =./include/
SRC_DIR=./src/
CC=gcc
CFLAGS= -g -Wextra -Wpedantic -I$(IDIR) -ltermcap

ODIR=obj

_DEPS = mts.h mts_handlers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = mts_builtins.o main.o termio.o tty.o signals.o handlers.o \
	   key_actions.o userio.o exec.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(addprefix $(SRC_DIR), %.c) $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

mts: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f mts
	rm -rf $(ODIR)
