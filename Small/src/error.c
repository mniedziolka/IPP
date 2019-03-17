#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "trie.h"
void callError() {
	fprintf(stderr, "%s", "ERROR\n");
}

void memoryError(char *line, struct TrieNode *root, char *historyA, char *historyB) {
	free(line);
	freeTrie(root);
	if (historyA) {
		free(historyA);
	}
	if (historyB) {
		free(historyB);
	}
	exit(1);
}