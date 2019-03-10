#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    struct TrieNode *root = NULL;

    while (flag == 1 && curr_char != -1) {
    	switch (curr_char) {
    		case '\n':
                ; //poprawic
    			int32_t cmd = getCommand(n, line, command);
                uint32_t index = 0;
                char *historyA = NULL, *historyB = NULL;
                uint64_t energy;

                uint8_t is_ok = 1;

                if (!cmd) {
                    is_ok = 0;
                } else {
                    if (cmd == 3 || cmd == 5) {
                        historyA = getHistory(&line[5]);
                        index += 5;
                    }
                    if (cmd == 2 || cmd == 4) {
                        historyA = getHistory(&line[6]);
                        index += 6;
                    }
                    if (cmd == 1) {
                        historyA = getHistory(&line[7]);
                        index += 7;
                    }

                    if (!historyA) {
                        is_ok = 0;
                    }
                }

                if (is_ok) {
                    index += strlen(historyA) + 1;
                    if (cmd == 4) {
                        if (line[index] == '\0') {
                            printf("NIEMAARGUMENTU2\n");
                            //printf("%lu\n", getEnergyTrie()) //dodać
                        } else {
                            energy = getEnergy(&line[index]);
                            if (!energy) {
                                is_ok = 0;
                            } else {
                                printf("%lu\n", energy);
                            }
                        }
                    }

                    if (cmd == 5) {
                        historyB = getHistory(&line[index]);
                        if (!historyB) {
                            is_ok = 0;
                        }
                        printf("%s\n", historyB);
                    }
                }

                if (!is_ok) {
                    callError();
                    // if (readGarbage()) {
                    //     flag = 0;
                    // }
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
    freeTrie(root);
    free(line);

    return 0;
}