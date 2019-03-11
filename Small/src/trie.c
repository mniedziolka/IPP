#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"


struct TrieNode *newNode() {
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	
	node->energy = malloc(sizeof(uint64_t));
	node->ends_here = 0;
	for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}


struct TrieNode *getNode(struct TrieNode *root, const char *key) {
	uint32_t key_length = strlen(key);

	struct TrieNode *node = root;
	for (uint32_t i = 0; i < key_length; i++){
		uint32_t curr = key[i] - '0';
		printf("%u<--\n", curr);
		if (!node->children[curr]) {
			return NULL;
		}
		node = node->children[curr];
	}
	if (node) {
		printf("ZWRACAMSENSOWNIE\n");
	}
	return node;
}


void freeTrie(struct TrieNode *node) {
	if (!node) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			freeTrie(node->children[i]);
			node->children[i] = NULL;
		}
		node = NULL;
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
	freeTrie(getNode(root, key));
}


uint8_t validTrie(struct TrieNode *root, const char *key) {
	struct TrieNode *node = getNode(root, key);
	return (node != NULL);
}


void energyUpdateTrie(struct TrieNode *root, const char *key, uint64_t energy) {
	getNode(root, key)->energy = &energy; //wskaźnik
}


uint64_t getEnergyTrie(struct TrieNode *root, const char *key) {
	return *(getNode(root, key)->energy);
}


void equalTrie(struct TrieNode *root, const char *keyA, const char *keyB) {
	struct TrieNode *pointerA = getNode(root, keyA), *pointerB = getNode(root, keyB);
	if (pointerA) {
		if (pointerB) {
			uint64_t curr_energy = (*pointerA->energy + *pointerB->energy) / 2;
			pointerA->energy = &curr_energy;
			pointerB->energy = pointerA->energy;
		} else {
			pointerB->energy = pointerA->energy;
		}
	} else {
		pointerA->energy = pointerB->energy;
	}
}
