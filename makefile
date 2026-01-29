CFLAGS = -Werror -Wall

all:
	g++ main.c $(CFLAGS) -o brainfk

generator:
	g++ generator/main.c $(CFLAGS) -o brainfk-gen

clean:
	rm brainfk
