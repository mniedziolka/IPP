#ifndef ERROR_H
#define ERROR_H

#include "trie.h"

void callError();
void memoryError(char *line, struct TrieNode *root, char *historyA, char *historyB);

#endif //ERROR_H