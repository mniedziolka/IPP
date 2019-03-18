#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "trie.h"


void callError() {
	fprintf(stderr, "%s", "ERROR\n");
}

void memoryError(char *line, struct TrieNode *root) {
	free(line);
	freeTrie(root);
	exit(1);
}