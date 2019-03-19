#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "findunion.h"
#include "trie.h"


struct TrieNode *newNode() {
	// Stwórz węzeł w drzewie Trie.
	struct TrieNode *node = malloc(sizeof(struct TrieNode));
	if (!node) {
		return NULL;
	}

	// Stwórz węzeł reprezentanta do findunion.
	struct FUNode *temp = malloc(sizeof(struct FUNode));
	if (!temp) {
		return NULL;
	}

	node->non_zero_energy = 0;
	for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	temp->indeg = 1;
	temp->energy = 0;
	temp->rep = temp;
	node->rep_energy = temp;

	return node;
}


static struct TrieNode *getNode(struct TrieNode *root, const char *key, const int64_t n) {
	struct TrieNode *node = root;
	for (uint32_t i = 0; i < n; i++){
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			return NULL;
		}
		node = node->children[curr];
	}

	return node;
}


void freeTrie(struct TrieNode *node) {
	if (node) {
		for (uint32_t i = 0; i < ALPHABET_SIZE; i++) {
			freeTrie(node->children[i]);
			node->children[i] = NULL;
		}
		freeFU(node->rep_energy);
		free(node);
	}
}


bool insertTrie(struct TrieNode *root, const char *key, const int64_t n) {
	struct TrieNode *node = root;
	for (uint32_t i = 0; i < n; i++) {
		uint32_t curr = key[i] - '0';
		if (!node->children[curr]) {
			struct TrieNode *temp = newNode();
			if (temp) {
				node->children[curr] = temp;
			} else {
				return false;
			}
		}
		node = node->children[curr];
	}

	return true;
}


// Usuń wszystko od ostatniego wierzchołka key w dół.
// Usuń krawędź do ostatniego wierzchołka.
void removeTrie(struct TrieNode *root, const char *key, const int64_t n) {
	char last = key[n - 1];
	struct TrieNode *node = getNode(root, key, n - 1);
	if (node) {
		freeTrie(node->children[last-'0']);
		node->children[last-'0'] = NULL;
	}
}


bool validTrie(struct TrieNode *root, const char *key, const int64_t n) {
	struct TrieNode *node = getNode(root, key, n);
	return (node != NULL);
}


bool energyUpdateTrie(struct TrieNode *root, const char *key, const int64_t n, uint64_t energy) {
	struct TrieNode *node = getNode(root, key, n);

	if (!node) {
		return false;
	}
	
	node->non_zero_energy = 1;
	findRepresentative(node->rep_energy)->energy = energy;

	return true;
}


uint64_t getEnergyTrie(struct TrieNode *root, const char *key, const int64_t n) {
	struct TrieNode *node = getNode(root, key, n);

	if (node && node->non_zero_energy) {
		return findRepresentative(node->rep_energy)->energy;
	}

	return 0;
}


bool equalTrie(struct TrieNode *root, const char *keyA, const int64_t n, const char *keyB, const int64_t m) {
	struct TrieNode *nodeA = getNode(root, keyA, n);
	struct TrieNode *nodeB = getNode(root, keyB, m);

	if (nodeA == NULL || nodeB == NULL) {
		return false;
	}
	if (nodeA == nodeB) {
		return true;
	}
	if (!nodeA->non_zero_energy && !nodeB->non_zero_energy) {
		return false;
	}

	nodeA->non_zero_energy = 1;
	nodeB->non_zero_energy = 1;
	unionNodes(nodeA->rep_energy, nodeB->rep_energy);

	return true;
}