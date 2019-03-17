CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2 -g
VPATH=src:inc

all: quantization

quantization: parser.o trie.o main.o findunion.o error.o
	$(CC) $(CFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -I inc -c $<

clean:
	rm -rf quantization *.o

.PHONY: all clean
