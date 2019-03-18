#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h> //<<<<>>>>

#include "findunion.h"

#define ALPHABET_SIZE 4
//ukryć strukturę w pliku c
//boole zamiast uint8
struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint8_t non_zero_energy;
	struct FUNode *rep_energy; //reprezentant
};

struct TrieNode *newNode();
void freeTrie(struct TrieNode *node);
uint8_t insertTrie(struct TrieNode *root, const char *key, const int64_t n);
void removeTrie(struct TrieNode *root, const char *key, const int64_t n);
uint8_t validTrie(struct TrieNode *root, const char *key, const int64_t n);
uint8_t energyUpdateTrie(struct TrieNode *root, const char *key, const int64_t n, const uint64_t energy);
uint64_t getEnergyTrie(struct TrieNode *root, const char *key, const int64_t n);
uint8_t equalTrie(struct TrieNode *root, const char *keyA, const int64_t n, const char *keyB, const int64_t m);

#endif //TRIE_H
