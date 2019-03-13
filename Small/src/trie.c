#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "findunion.h"
#include "trie.h"


struct TrieNode *newNode() {
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	
	node->rep_energy = malloc(sizeof(struct FUNode));
	node->non_zero_energy = 0;
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
		if (!node->children[curr]) {
			return NULL;
		}
		node = node->children[curr];
	}

	return node;
}


void freeTrie(struct TrieNode *node) {
	//dodać poprawne usuwanie nodów z FU
	if (node) {
		node->rep_energy->size--;
		for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
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

}

//usuwam wszystko od wierzchołka w dół, a potem ścieżkę do niego
void removeTrie(struct TrieNode *root, char *key) {
	//blef
	uint32_t index_last = strlen(key) - 1;
	char last = key[index_last];
	key[index_last] = '\0';
	struct TrieNode *node = getNode(root, key);
	freeTrie(node->children[last-'0']);
	node->children[last-'0'] = NULL;
}


uint8_t validTrie(struct TrieNode *root, const char *key) {
	struct TrieNode *node = getNode(root, key);
	return (node != NULL);
}


void energyUpdateTrie(struct TrieNode *root, const char *key, uint64_t energy) {
	struct TrieNode *node = getNode(root, key);
	if (node->non_zero_energy) {
		findRepresentative(node->rep_energy)->energy = energy;
	} else {
		node->non_zero_energy = 1;
		struct FUNode *temp = NULL;
		temp->size = 1;
		temp->energy = energy;
		temp->rep = temp;
		node->rep_energy = temp;
	}
	
}


uint64_t getEnergyTrie(struct TrieNode *root, const char *key) {
	struct TrieNode *node = getNode(root, key);
	if (node->non_zero_energy) {
		return findRepresentative(node->rep_energy)->energy;
	} else {
		return 0;
	}
	
}


void equalTrie(struct TrieNode *root, const char *keyA, const char *keyB) {
	struct TrieNode *nodeA = getNode(root, keyA);
	struct TrieNode *nodeB = getNode(root, keyB);
	unionNodes(nodeA->rep_energy, nodeB->rep_energy);
}