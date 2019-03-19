#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Wczytaj wszystkie znaki do napotkania '\n' lub EOF.
uint8_t readGarbage() {
	char garbage = getchar();

	while (garbage != '\n') {
		if (garbage == -1) {
			return 1;
		}
		garbage = getchar();
	}

	return 0;
}


uint8_t checkChar(char c) {
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || (c == ' '));
}


// Przeiteruj się po każdej dostępnej komendzie i porównaj z line.
// Jeśli nie dopasowano wzorca zwróć -1.
int32_t getCommand(uint32_t n, char *line, char *command[5]) {
	for (uint32_t i = 0; i < 5; i++) {
		int8_t check = i;
		uint32_t curr_length = strlen(command[i]);
		
		if (n < curr_length) {
			check = -1;
		} else {
			for (uint32_t j = 0; j < curr_length; j++){
				if (line[j] != command[i][j]) {
					check = -1;
					break;
				}
			}
		}
		
		if (check != -1) {
			return check;
		}
	}

	return -1;
}


int64_t getHistoryLength(char *line) {
	int64_t result = 0;

	while ('0' <= *line && *line <= '3') {
		result++;
		line++;
	}
	
	return result;
}


uint64_t getEnergy(char *line) {
	uint64_t energy = 0;

	if (line[0] != ' ') {
		return 0;
	}
	line++;
	
	// Sprawdź czy następna cyfra nie przekroczy zakresu uint64_t.
	while (*line != '\0') {
		if ('0' <= *line && *line <= '9' && (UINT64_MAX - *line + '0') / 10 >= energy) {
			energy = energy * 10 + *line - '0';
		} else {
			return 0;
		}
		line++;
	}

	return energy;
}
