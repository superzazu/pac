bin = pac
src = $(wildcard *.c) z80/z80.c
obj = $(src:.c=.o)

CFLAGS = -g -Wall -Wextra -O2 -std=c99 -pedantic -Wno-gnu-binary-literal $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

ifeq ($(MAKECMDGOALS),web)
CC = emcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -pedantic -Wno-gnu-binary-literal -s USE_SDL=2
LDFLAGS = -s USE_SDL=2 --preload-file roms@/ -o $(bin).html
endif

.PHONY: all clean

all: $(bin)

$(bin): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

web: $(bin)

clean:
	-rm $(bin) $(obj)
	-rm $(bin).html $(bin).js $(bin).data $(bin).wasm
