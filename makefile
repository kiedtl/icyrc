BIN = irc
SRC = irc.c utf8.c
OBJ = $(SRC:.c=.o)

CFLAGS = -std=c99 -O1 -D_POSIX_C_SOURCE=201112 -D_GNU_SOURCE \
	 -D_XOPEN_CURSES -D_XOPEN_SOURCE_EXTENDED=1 \
	 -D_DEFAULT_SOURCE -D_BSD_SOURCE \
	 -I. -Isub/ccommon
LDFLAGS = -lncursesw -lssl -lcrypto

all: ${BIN}

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(OBJ)

install:
	install -Dm755 ${BIN} $(DESTDIR)$(PREFIX)/bin/${BIN}

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/${BIN}

clean:
	rm -f ${BIN} *.o

.PHONY: all clean
