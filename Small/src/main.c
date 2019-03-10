#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "trie.h"

int32_t main() {
    char *command[5] = {"DECLARE", "REMOVE", "VALID", "ENERGY", "EQUAL"};
	size_t size_line = 32, n = 0; //n wskazuje na zaostatni
	char *line;
	line = malloc(size_line * sizeof(char));
	assert(line);

	uint8_t is_newline = 1, flag = 1; //is EOF reached in while

    int32_t curr_char = getchar();
    while (flag == 1 && curr_char != -1) {
    	switch (curr_char) {
    		case '\n':
                ; //poprawic
    			// printf("%d<---\n", (int)n);
			    // for(uint32_t i = 0; i < n; i++){
			    // 	printf("%c", line[i]);
			    // }
			    // printf("\n\n");
    			int32_t cmd = getCommand(n, line, command);
                if (!cmd) {
                    callError();
                    readGarbage();
                } else {
                    
                }
                
                free(line);
    			is_newline = 1;
    			n = 0;
    			size_line = 32;
    			line = malloc(size_line * sizeof(char));
				assert(line);
                curr_char = getchar();
    			break;

    		case '#':
    			if (is_newline == 0) {
                    callError();
    			}

                if (readGarbage() == 1) {
                    flag = 0;
                }
                free(line);
                is_newline = 1;
                n = 0;
                size_line = 32;
                line = malloc(size_line * sizeof(char));
                assert(line);
                curr_char = getchar();
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
                    free(line);
    				is_newline = 1;
    				n = 0;
    				size_line = 32;
    				line = malloc(size_line * sizeof(char));
                    assert(line);
    			}
                curr_char = getchar();
    			break;
    	}
    }

    //Pamietaj zwolnic pamiec
    free(line);

    return 0;
}