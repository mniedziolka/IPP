#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"


struct TrieNode *newNode() {
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	
	node->energy = 0;
	node->ends_here = 0;
	for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}


struct Trienode *getNode(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++){
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			return node->children[curr];
		}
		node = node->children[curr];
	}
	return node;
}


void freeTrie(struct TrieNode *node) {
	if (!node) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			freeTrie(node->children[i]);
		}
		//free(node->energy);
		//free(node->ends_here);
		free(node);
	}
	//valgrind --leak-check=full  ./q
}


void insertTrie(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++) {
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			node->children[curr] = newNode();
		}
		node = node->children[curr];
	}

	node->ends_here = 1;
}


void removeTrie(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++) {
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			return;
		}
		node = node->children[curr];
	}

	freeTrie(node);
}

uint8_t validTrie(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++){
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			return 0;
		}
		node = node->children[curr];
	}
	return 1;
}


void energyUpdateTrie(struct TrieNode *root, const char *key, const uint64_t energy) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++) {
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			return;
		}
		node = node->children[curr];
	}
	node->energy = energy;
}


uint64_t getEnergyTrie(struct TrieNode *root, const char *key) {
	if (!validTrie(root, key)) {
		return -1;
	}

	uint32_t key_length = strlen(key);
	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++) {
		uint32_t curr = key[i] - '0';
		node = node->children[curr];
	}
	return node->energy;
}

void equalTrie(struct TrieNode *root, const char *keyA, const char *keyB) {

}