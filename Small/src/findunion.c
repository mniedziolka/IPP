#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "findunion.h"


struct FUNode *findRepresentative(struct FUNode *node) {
	//printf("%p---\n", node);
	if (node->rep == node) {
		return node;
	}

	struct FUNode *curr = node->rep;

	node->rep->size--;
	node->rep = findRepresentative(node->rep);
	node->rep->size++;
	

	if (curr->size == 0) { 
		//jeśli nic nie wskazuje na wierzchołek zwolnij
		curr->rep = NULL;
		free(curr);
	}

	return node->rep;
}


void unionNodes(struct FUNode *nodeA, struct FUNode *nodeB) {
	struct FUNode *rep_nodeA = findRepresentative(nodeA);
	struct FUNode *rep_nodeB = findRepresentative(nodeB);

	uint64_t energyA = rep_nodeA->energy, energyB = rep_nodeB->energy;
	uint64_t final_energy = 0;

	if (energyA == 0 && energyB != 0) {
		final_energy = energyB;
	}

	if (energyA != 0 && energyB == 0) {
		final_energy = energyA;
	}

	if (energyA != 0 && energyB != 0) {
		//cuda z powodu ryzyka przekroczenia zakresu
		final_energy = (energyA / 2) + (energyB / 2);
		if (energyA % 2 == 1 && energyB % 2 == 1) {
			final_energy++;
		}
	}

	if (rep_nodeA != rep_nodeB) {
		if (rep_nodeA->size > rep_nodeB->size) {
			rep_nodeA->energy = final_energy;
			rep_nodeA->size++;
			rep_nodeB->rep = rep_nodeA;
		} else {
			rep_nodeB->energy = final_energy;
			rep_nodeB->size++;
			rep_nodeA->rep = rep_nodeB;
		}
	}
}
