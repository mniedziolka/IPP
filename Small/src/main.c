#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "trie.h"

int32_t main() {
    char *command[5] = {"DECLARE", "REMOVE", "VALID", "ENERGY", "EQUAL"};
	size_t size_line = 32, n = 0; //n wskazuje na zaostatni
	char *line = malloc(size_line * sizeof(char));
	if (!line) {
        exit(1);
    }

	uint8_t is_newline = 1, flag = 1; //is EOF reached in while

    int32_t curr_char = getchar();

    struct TrieNode *root = newNode();

    //dopóki nie napotkamy EOF
    while (flag == 1 && curr_char != -1) {
    	switch (curr_char) {
    		case '\n':
                if (n != 0) {
                    int32_t cmd = getCommand(n, line, command);
                    uint32_t index = 0; //aktualny indeks do parsowania linii
                    char *historyA = NULL, *historyB = NULL;
                    uint64_t energy = 0;
                    line[n] = '\0';
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

                        if (!historyA || strlen(historyA) == 0) {
                            is_ok = 0;
                        }
                    }

                    uint8_t arg = 2; //liczba argumentów do ENERGY
                    if (is_ok) {
                        index += strlen(historyA) + 1;
                        if (cmd == 1 || cmd == 2 || cmd == 3) {
                            if (line[index] != '\0') {
                                is_ok = 0;
                            }
                        }
                        if (cmd == 4) {
                            if (line[index] == '\0') {
                                arg = 1;
                            } else {
                                energy = getEnergy(&line[index]);
                                if (!energy) {
                                    is_ok = 0;
                                }
                            }
                        }

                        if (cmd == 5) {
                            historyB = getHistory(&line[index]);
                            if (!historyB || strlen(historyB) == 0) {
                                is_ok = 0;
                            }
                            index += strlen(historyB) + 1;
                            if (line[index] != '\0') {
                                is_ok = 0;
                            }
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
                                //printf("%d\n", validTrie(root, historyA));
                                if (validTrie(root, historyA)) {
                                    printf("%s\n", "YES");
                                } else {
                                    printf("%s\n", "NO");
                                }
                                break;
                            case 4:
                                if (arg == 1) {
                                    uint64_t energy = getEnergyTrie(root, historyA);
                                    if (energy == 0) {
                                        callError();
                                    } else {
                                        printf("%lu\n", energy);
                                    }
                                } else {
                                    if (energyUpdateTrie(root, historyA, energy)) {
                                        printf("%s\n", "OK");
                                    } else {
                                        callError();
                                    }
                                }
                                break;
                            case 5:
                                if (equalTrie(root, historyA, historyB)) {
                                    printf("%s\n", "OK");
                                } else {
                                    callError();
                                }
                                break;
                        }
                    }
                    if (historyA) {
                        free(historyA);
                    }

                    if (historyB) {
                        free(historyB);
                    }
                }

    			
                
                free(line);
    			is_newline = 1;
    			n = 0;
    			size_line = 32;
    			line = malloc(size_line * sizeof(char));
				if (!line) {
                    exit(1);
                }
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
                if (!line) {
                    exit(1);
                }
    			break;

    		default:
    			if (checkChar(curr_char)) {
                    is_newline = 0;
    				if (n == size_line - 1) {
    					size_line *= 2;
                        char *temp = realloc(line, size_line * sizeof(char));
                        if (!temp) {
                            exit(1);
                        }
    					line = temp;    				
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
                    if (!line) {
                        exit(1);
                    }
    			}
    			break;
    	}
        curr_char = getchar();
    }

    //Pamietaj zwolnic pamiec
    freeTrie(root);
    free(line);

    return 0;
}
