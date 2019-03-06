#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"

struct TrieNode *newNode() {
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	
	node->radix_length = 0;
	node->energy = 0;
	for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}

void insert(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (int i = 0; i < key_length; i++) {
		if (!node->children[i]) {
			node->children[i] = newNode();
		}
		node = node->children[i];
	}

}