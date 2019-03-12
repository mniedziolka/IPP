#ifndef TRIE_H
#define TRIE_H

#include "findunion.h"

#define ALPHABET_SIZE 4

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint8_t non_zero_energy;
	struct FUNode *rep_energy; //reprezentant
};

struct TrieNode *newNode();
void freeTrie(struct TrieNode *node);
void insertTrie(struct TrieNode *root, const char *key);
void removeTrie(struct TrieNode *root, char *key);
uint8_t validTrie(struct TrieNode *root, const char *key);
void energyUpdateTrie(struct TrieNode *root, const char *key, const uint64_t energy);
uint64_t getEnergyTrie(struct TrieNode *root, const char *key);
void equalTrie(struct TrieNode *root, const char *keyA, const char *keyB);

#endif //TRIE_H
