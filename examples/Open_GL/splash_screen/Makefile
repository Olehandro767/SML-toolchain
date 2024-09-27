CC = clang
CFLAGS = -Wall -O4
LDFLAGS = -pthread -lm -lX11 -lGL -lGLU -lSDL2 -lSDL2_image -I../../../src/

all: main

main: main.c
	mkdir ./build
	cp application_logo.png ./build/application_logo.png
	$(CC) $(CFLAGS) -c -o ./build/sml_async_impl.o ../../../src/utils/async/linux_async.c
	$(CC) $(CFLAGS) -c -o ./build/sml_screen_impl.o ../../../src/media/screen/linux_screen.c
	$(CC) $(CFLAGS) -c -o ./build/sml_common_impl.o ../../../src/window/sml_common_impl.c $(LDFLAGS)
	$(CC) $(CFLAGS) -c -o ./build/str_impl.o ../../../src/utils/type/string_impl.c
	$(CC) $(CFLAGS) -c -o ./build/sml_window.o ../../../src/window/Open_GL/window_X11.c -nostartfiles $(LDFLAGS)
	$(CC) $(CFLAGS) -c -o ./build/main.o main.c -I../../../src/
	$(CC) $(CFLAGS) -o ./build/main ./build/main.o ./build/sml_window.o ./build/str_impl.o ./build/sml_common_impl.o ./build/sml_screen_impl.o ./build/sml_async_impl.o $(LDFLAGS)

clean:
	rm -f -R ./build
