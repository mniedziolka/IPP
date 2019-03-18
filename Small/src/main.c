#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "parser.h"
#include "trie.h"

int32_t main() {
    char *command[5] = {"DECLARE", "REMOVE", "VALID", "ENERGY", "EQUAL"};
	size_t size_line = 32, n = 0; //n wskazuje na zaostatni
	char *line = malloc(size_line * sizeof(char));
	if (!line) {
        memoryError(line, NULL);
    }

	uint8_t is_newline = 1, flag = 1; //flaga mówi czy napotkaliśmy EOF w środku whila

    int32_t curr_char = getchar();

    struct TrieNode *root = newNode();

    //dopóki nie napotkamy EOF
    while (flag == 1 && curr_char != -1) {
    	switch (curr_char) {
    		case '\n':
                if (n != 0) {
                    int32_t cmd = getCommand(n, line, command);
                    int64_t historyA_length = -1, historyB_length = -1; //aktualny indeks do parsowania linii
                    char *historyA_pointer = NULL, *historyB_pointer = NULL;
                    uint64_t energy = 0;
                    line[n] = '\0';
                    bool is_ok = true;
                    uint64_t index = 0;

                    if (cmd == -1) {
                        is_ok = false;
                    } else {
                        index += strlen(command[cmd]);
                        if (line[index] == ' ') {
                            index++;
                            historyA_pointer = &line[index];
                            historyA_length = getHistoryLength(&line[index]);
                            if (historyA_length == -1) {
                                is_ok = false;
                            }
                            index += historyA_length;
                        } else {
                            is_ok = false;
                        }
                    }
                    uint8_t arg = 2; //liczba argumentów do ENERGY
                    if (is_ok) {
                        if (cmd == 0 || cmd == 1 || cmd == 2) {
                            if (line[index] != '\0') {
                                is_ok = false;
                            }
                        }
                        if (cmd == 3) {
                            if (line[index] == '\0') {
                                arg = 1;
                            } else {
                                if (line[index] != ' ') {
                                    is_ok = false;
                                } else {
                                    energy = getEnergy(&line[index]);
                                    if (!energy) {
                                        is_ok = false;
                                    }
                                }
                            }
                        }

                        if (cmd == 4) {
                            if (line[index] == ' '){
                                index++;
                                historyB_pointer = &line[index];
                                historyB_length = getHistoryLength(&line[index]);
                                if (historyB_length == -1) {
                                    is_ok = false;
                                } else {
                                    index += historyB_length;
                                    if (line[index] != '\0') {
                                        is_ok = false;
                                    }
                                }
                            } else {
                                is_ok = false;
                            }
                            
                        }
                    }

                    if (!is_ok) {
                        callError();
                    } else {
                        switch (cmd) {
                            case 0:
                                if (insertTrie(root, historyA_pointer, historyA_length)) {
                                    printf("%s\n", "OK");
                                } else {
                                    memoryError(line, root);
                                }
                                break;
                            case 1:
                                removeTrie(root, historyA_pointer, historyA_length);
                                printf("%s\n", "OK");
                                break;
                            case 2:
                                if (validTrie(root, historyA_pointer, historyA_length)) {
                                    printf("%s\n", "YES");
                                } else {
                                    printf("%s\n", "NO");
                                }
                                break;
                            case 3:
                                if (arg == 1) {
                                    uint64_t energy = getEnergyTrie(root, historyA_pointer, historyA_length);
                                    if (energy == 0) {
                                        callError();
                                    } else {
                                        printf("%lu\n", energy);
                                    }
                                } else {
                                    if (energyUpdateTrie(root, historyA_pointer, historyA_length, energy)) {
                                        printf("%s\n", "OK");
                                    } else {
                                        callError();
                                    }
                                }
                                break;
                            case 4:
                                if (equalTrie(root, historyA_pointer, historyA_length, historyB_pointer, historyB_length)) {
                                    printf("%s\n", "OK");
                                } else {
                                    callError();
                                }
                                break;
                        }
                    }
                }
                
                free(line);
    			is_newline = 1;
    			n = 0;
    			size_line = 32;
    			line = malloc(size_line * sizeof(char));
				if (!line) {
                    memoryError(line, root);
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
                    memoryError(line, root);
                }
    			break;

    		default:
    			if (checkChar(curr_char)) {
                    is_newline = 0;
    				if (n == size_line - 1) {
    					size_line *= 2;
                        char *temp = realloc(line, size_line * sizeof(char));
                        if (!temp) {
                            memoryError(line, root);
                        }
    					line = temp;    				
                    }
    				line[n] = curr_char;
    				n++;
    			} else {
                    if (readGarbage() == 1) {
                        flag = 0;
                    }
                    if (flag){
                        callError();
                    }
                    free(line);
    				is_newline = 1;
    				n = 0;
    				size_line = 32;
    				line = malloc(size_line * sizeof(char));
                    if (!line) {
                        memoryError(line, root);
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
