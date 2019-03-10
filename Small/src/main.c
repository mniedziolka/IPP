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

    struct TrieNode *root = newNode();

    while (flag == 1 && curr_char != -1) {
    	switch (curr_char) {
    		case '\n':
                ; //poprawic
    			int32_t cmd = getCommand(n, line, command);
                uint32_t index = 0;
                char *historyA = NULL, *historyB = NULL;
                uint64_t energy = 0;

                uint8_t is_ok = 1;
                printf("Komenda: %d\n", cmd);
                if (!cmd) {
                    is_ok = 0;
                } else {
                    if (cmd == 3 || cmd == 5) {
                        printf("%c##\n", line[6]);
                        historyA = getHistory(&line[5]);
                        index += 5;
                    }
                    if (cmd == 2 || cmd == 4) {
                        printf("%c##\n", line[7]);
                        historyA = getHistory(&line[6]);
                        index += 6;
                    }
                    if (cmd == 1) {
                        printf("%c##\n", line[8]);
                        historyA = getHistory(&line[7]);
                        index += 7;
                    }

                    if (!historyA) {
                        is_ok = 0;
                    }
                }

                uint8_t arg = 2; //liczba argumentów do ENERGY
                if (is_ok) {
                    printf("%s<-\n", historyA);
                    index += strlen(historyA) + 1;
                    printf("%c %c####\n", line[index-1], line[index]);
                    if (cmd == 4) {
                        if (line[index] == '\0') {
                            arg = 1;
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
                } else {
                    switch (cmd) {
                        case 1:
                            insertTrie(root, historyA);
                            printf("%s\n", "OK");
                            break;
                        case 2:
                            removeTrie(root, historyA);
                            printf("%s\n", "OK");
                            break;
                        case 3:
                            printf("%s\n", historyA);
                            if (validTrie(root, historyA)) {
                                printf("%s\n", "YES");
                            } else {
                                printf("%s\n", "NO");
                            }
                            break;
                        case 4:
                            if (arg == 1) {
                                printf("%lu\n", getEnergyTrie(root, historyA));
                            } else {
                                energyUpdateTrie(root, historyA, energy);
                            }
                            break;
                        case 5:
                            equalTrie(root, historyA, historyB);
                            break;
                    }
                }
                free(historyA);
                free(historyB);
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
