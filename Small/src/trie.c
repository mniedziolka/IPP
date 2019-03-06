const uint32_t ALPHABET_SIZE = 4;

struct Node {
	struct Node *children[ALPHABET_SIZE];
	uint64_t energy;
};

struct Node *newNode(uint64_t energy) {
	struct Node *node = malloc(sizeof *node);
	
	char *radix
	node->energy = energy;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		node->children[i] = NULL;
	}

	return node;
}