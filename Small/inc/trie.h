#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 4

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];
	uint32_t radix_length;
	char *radix;
	uint64_t energy;
};

struct TrieNode *newNode();
void insert(struct TrieNode *root, const char *key);

#endif //TRIE_H