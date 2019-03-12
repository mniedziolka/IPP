#ifndef FINDUNION_H
#define FINDUNION_H

struct FUNode {
	struct FUNode *rep;
	uint32_t size;
	uint64_t energy;
};

struct FUNode *findRepresentative(struct FUNode *node);
void unionNodes(struct FUNode *nodeA, struct FUNode *nodeB);

#endif //FINDUNION_H
