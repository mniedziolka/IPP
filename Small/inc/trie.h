#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 4

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint8_t ends_here;
	uint64_t *energy; //reprezentant
};

struct TrieNode *newNode();
void freeTrie(struct TrieNode *node);
void insertTrie(struct TrieNode *root, const char *key);
struct TrieNode *searchTrie(struct TrieNode *root, const char *key);
uint8_t validTrie(struct TrieNode *root, const char *key);
void energyUpdateTrie(struct TrieNode *root, const char *key, const uint64_t energy);
uint64_t getEnergyTrie(struct TrieNode *root, const char *key);

#endif //TRIE_H