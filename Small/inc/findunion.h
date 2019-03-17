#ifndef FINDUNION_H
#define FINDUNION_H

struct FUNode {
	struct FUNode *rep;
	uint32_t indeg;
	uint64_t energy;
};

struct FUNode *findRepresentative(struct FUNode *node);
void unionNodes(struct FUNode *nodeA, struct FUNode *nodeB);
void freeFU(struct FUNode *node);
#endif //FINDUNION_H
