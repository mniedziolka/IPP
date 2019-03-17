#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint8_t readGarbage() {
	char garbage = getchar();

	while (garbage != '\n') {
		if (garbage == -1) {
			return 1; //EOF reached
		}
		garbage = getchar();
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


char *getHistory(char *line) {
	size_t size_history = 32, curr = 0;
	char *history = malloc(size_history * sizeof(char));
	if (!history) {
		free(history);
		return NULL;
	}

	if (line[0] != ' ') {
		*history = '\0';
		return history;
	}
	line++;

	for (uint32_t i = 0; i < strlen(line); i++) {
		if ('0' <= line[i] && line[i] <= '3') {
			if (curr == size_history - 1) {
				size_history *= 2;
				char *temp = realloc(history, size_history * sizeof(char));
				if (!temp) {
					free(history);
					return NULL;
				}
				history = temp;
			}
			history[curr] = line[i];
			curr++;
		} else if (line[i] == ' ') {
			history[curr] = '\0';
			return history;
		} else {
			//zwróć pustą historię dla błędu
			*history = '\0';
			return history;
		}
	}
	history[curr] = '\0';
	return history;
}


uint64_t getEnergy(char *line) {
	if (line[0] != ' ') {
		return 0;
	}
	line++;
	uint64_t size = 0;
	while (*line != '\0') {
		if ('0' <= *line && *line <= '9' && (UINT64_MAX - *line + '0') / 10 >= size) {
			size = size * 10 + *line - '0';
		} else {
			return 0;
		}
		line++;
	}

	return size;
}
