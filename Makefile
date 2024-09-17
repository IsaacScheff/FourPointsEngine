CC = clang
CFLAGS = -I./include -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_image -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image

all: main

# Include both main.c and engine.c to compile and link them together
main: src/main.c src/engine.c src/grid.c
	$(CC) $(CFLAGS) -o main src/main.c src/engine.c src/grid.c $(LDFLAGS)

clean:
	rm -f main