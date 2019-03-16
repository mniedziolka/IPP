#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "findunion.h"
#include "trie.h"


struct TrieNode *newNode() {
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	
	node->non_zero_energy = 0;
	for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	struct FUNode *temp = malloc(sizeof(struct FUNode));
	temp->size = 1;
	temp->energy = 0;
	temp->rep = temp;

	node->rep_energy = temp;

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
		for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
			freeTrie(node->children[i]);
			node->children[i] = NULL;
		}
		freeFU(node->rep_energy);
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
	uint32_t index_last = strlen(key) - 1;
	char last = key[index_last];
	key[index_last] = '\0';
	struct TrieNode *node = getNode(root, key);
	if (node) {
		//printf("%c\t%d", last, last - '0');
		freeTrie(node->children[last-'0']);
		node->children[last-'0'] = NULL;
	}
}


uint8_t validTrie(struct TrieNode *root, const char *key) {
	struct TrieNode *node = getNode(root, key);
	return (node != NULL);
}


uint8_t energyUpdateTrie(struct TrieNode *root, const char *key, uint64_t energy) {
	struct TrieNode *node = getNode(root, key);
	if (!node) {
		return 0;
	}
	
	node->non_zero_energy = 1;
	findRepresentative(node->rep_energy)->energy = energy;

	return 1;
}


uint64_t getEnergyTrie(struct TrieNode *root, const char *key) {
	struct TrieNode *node = getNode(root, key);

	if (node && node->non_zero_energy) {
		return findRepresentative(node->rep_energy)->energy;
	} else {
		return 0;
	}
	
}


uint8_t equalTrie(struct TrieNode *root, const char *keyA, const char *keyB) {
	struct TrieNode *nodeA = getNode(root, keyA);
	struct TrieNode *nodeB = getNode(root, keyB);
	if (nodeA == NULL || nodeB == NULL) {
		return 0;
	}
	if (!nodeA->non_zero_energy && !nodeB->non_zero_energy) {
		return 0; //jeśli obie nie mają energii
	}
	nodeA->non_zero_energy = 1;
	nodeB->non_zero_energy = 1;
	unionNodes(nodeA->rep_energy, nodeB->rep_energy);

	return 1;
}