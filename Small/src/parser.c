#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void callError() {
	printf("ERROR\n");
}

uint8_t readGarbage() {
	char garbage;

	if (scanf("%c", &garbage) != 1) {
		return 1; //EOF reached
	}
	while (garbage != '\n') {
		if (scanf("%c", &garbage) != 1) {
			return 1; //EOF reached
		}
	}

	return 0;
}

uint8_t checkChar(char c) {
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'));
}

void parseLine(int n, char *line) {
	
}