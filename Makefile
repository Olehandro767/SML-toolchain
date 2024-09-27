CC = clang
CFLAGS = -Wall -O4 -pthread -c
LDFLAGS = -nostartfiles -lSDL2 -lSDL2_image -lGL -lGLEW -lm -I./src/

all: main

main: ./src/window/window_SDL_GL.c
	mkdir ./build
	$(CC) $(CFLAGS) -o ./build/lgui_window.o ./src/window/window_SDL_GL.c $(LDFLAGS)

clean:
	rm -f -R ./build