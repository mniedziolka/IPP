#ifndef ERROR_H
#define ERROR_H

#include "trie.h"

void callError();
void memoryError(char *line, struct TrieNode *root);

#endif //ERROR_H