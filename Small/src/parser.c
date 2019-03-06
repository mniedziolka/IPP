#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || (c == ' '));
}

int32_t getCommand(uint32_t n, char *line, char *command[5]) {
	for (uint32_t i = 0; i < 5; i++) {
		uint8_t check = i + 1;
		if (n < strlen(command[i])) {
			check = 0;
		} else {
			for (uint32_t j = 0; j < strlen(command[i]); j++){
				if (line[j] != command[i][j]) {
					check = 0;
					break;
				}
			}
		}
		
		if (check) {
			return check;
		}
	}

	return 0;
}

void parseLine(uint32_t n, char *line) {


}