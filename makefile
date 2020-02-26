#
# icyrc: simple irc client
# (c) Kied Llaentenn
# See the LICENSE for more information
#

DESTDIR =
PREFIX  = /usr/local/

BIN     = irc
SRC     = $(BIN).c utf8.c sub/map/src/map.c
OBJ     = $(SRC:.c=.o)

INC	= -I. -Isub/ccommon/ -Isub/map/src

CC      = gcc
LD      = gold
CFLAGS  = -std=c99 -pedantic $(INC) \
          -D_POSIX_C_SOURCE=201112 -D_GNU_SOURCE \
          -D_XOPEN_CURSES -D_XOPEN_SOURCE_EXTENDED=1 \
          -D_DEFAULT_SOURCE -D_BSD_SOURCE
LDFLAGS = -fuse-ld=$(LD) -lncursesw -lssl -lcrypto

all: debug

clean:
	rm -f $(BIN) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) $(CFLAGS_OPT) -c $< -o $(<:.c=.o)

debug: CFLAGS_OPT := -O1 -ggdb
debug: $(BIN)

release: CFLAGS_OPT := -O4 -s
release: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS_OPT) $(LDFLAGS)

install: $(BIN)
	install -m755 ./$(BIN) $(DESTDIR)/$(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(DESTDIR)/$(PREFIX)/bin/$(BIN)

.PHONY: all debug release clean install uninstall
