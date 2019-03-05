#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main() {
	size_t size_line = 32, n = 0; //n wskazuje na zaostatni
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
    			parseLine(n, line);
    			is_newline = 1;
    			n = 0;
    			size_line = 32;
    			line = malloc(size_line * sizeof(char));
				assert(line);
    			break;

    		case '#':
    			if (is_newline == 0) {
                    callError();
    			}

                if (readGarbage() == 1) {
                    flag = 0;
                }
                is_newline = 1;
                n = 0;
                size_line = 32;
                line = malloc(size_line * sizeof(char));
                assert(line);
    			break;

    		default:
    			if ( checkChar(curr_char) ) {
                    is_newline = 0;
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
                    assert(line);
    			}
    			break;
    	}
    }

    //Pamietaj zwolnic pamiec
    free(line);

    return 0;
}