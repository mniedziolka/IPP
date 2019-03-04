#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void callError(){
	printf("ERROR\n");
}

uint8_t readGarbage(){
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

inline uint8_t checkChar(char c){
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'));
}

int main() {
	size_t size_line = 32, n = 0;
	char curr_char, *line;
	line = malloc(size_line * sizeof(char));
	assert(line);

	uint8_t is_newline = 1, flag = 1; //is EOF reached in while

    while (flag == 1 && scanf("%c", &curr_char) == 1) {
    	switch (curr_char) {
    		case '\n':
    			// printf("%d<---\n", (int)n);
			    // for(uint32_t i = 0; i < n; i++){
			    // 	printf("%c", line[i]);
			    // }
			    // printf("\n\n");
    			is_newline = 1;
    			n = 0;
    			size_line = 32;
    			line = malloc(size_line * sizeof(char));
				assert(line);
    			break;
    		case '#':
    			if (is_newline == 1) {
    				is_newline = 0;
    				if (readGarbage() == 1) {
    					flag = 0;
    				}
    			} else {
    				callError();
    				if (readGarbage() == 1) {
    					flag = 0;
    				}
    				is_newline = 1;
    				n = 0;
    				size_line = 32;
    				line = malloc(size_line * sizeof(char));
    			}
    			break;
    		default:
    			if ( checkChar(curr_char) ) {
    				if (n == size_line - 1) {
    					size_line *= 2;
    					line = realloc(line, size_line * sizeof(char));
    				}
    				line[n] = curr_char;
    				n++;
    			} else {
    				callError();
    				if (readGarbage() == 1) {
    					flag = 0;
    				}
    				is_newline = 1;
    				n = 0;
    				size_line = 32;
    				line = malloc(size_line * sizeof(char));
    			}
    			break;
    	}
    }

    //Pamietaj zwolnic pamiec

    return 0;
}