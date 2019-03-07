#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 4

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint8_t ends_here;
	//uint32_t radix_length;
	//char *radix;
	uint64_t energy;
};

struct TrieNode *newNode();
void freeTrie(TrieNode *node);
void insert(struct TrieNode *root, const char *key);
uint8_t valid(struct TrieNode *root, const char *key);

#endif //TRIE_H