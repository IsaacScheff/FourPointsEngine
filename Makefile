CC = clang
CFLAGS = -I./include -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/lib -lSDL2

all: main

main: src/main.c src/engine.c
	$(CC) $(CFLAGS) -o main src/main.c src/engine.c $(LDFLAGS)

clean:
	rm -f main
