#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#include "findunion.h"

#define ALPHABET_SIZE 4

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint8_t non_zero_energy;
	struct FUNode *rep_energy; //reprezentant
};

struct TrieNode *newNode();
void freeTrie(struct TrieNode *node);
bool insertTrie(struct TrieNode *root, const char *key, const int64_t n);
void removeTrie(struct TrieNode *root, const char *key, const int64_t n);
bool validTrie(struct TrieNode *root, const char *key, const int64_t n);
bool energyUpdateTrie(struct TrieNode *root, const char *key, const int64_t n, const uint64_t energy);
uint64_t getEnergyTrie(struct TrieNode *root, const char *key, const int64_t n);
bool equalTrie(struct TrieNode *root, const char *keyA, const int64_t n, const char *keyB, const int64_t m);

#endif //TRIE_H
