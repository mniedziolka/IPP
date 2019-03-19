#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "findunion.h"


struct FUNode *findRepresentative(struct FUNode *node) {
	if (node->rep == node) {
		return node;
	}

	return findRepresentative(node->rep);
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
		// Średnia arytmetyczna z uwzględnieniem overflow uint64_t.
		final_energy = (energyA / 2) + (energyB / 2) + (energyA % 2 == 1 && energyB % 2 == 1);
	}

	if (rep_nodeA != rep_nodeB) {
		// Przepinam wierzchołek z mniejszą liczbą wchodzących na większą.
		if (rep_nodeA->indeg > rep_nodeB->indeg) {
			rep_nodeA->energy = final_energy;
			rep_nodeA->indeg++;
			rep_nodeB->rep = rep_nodeA;
		} else {
			rep_nodeB->energy = final_energy;
			rep_nodeB->indeg++;
			rep_nodeA->rep = rep_nodeB;
		}
	}
}


// Przejdź po ścieżce w górę i zmniejsz indeg.
// Jeśli jesteś ostatnią krawędzią wchodzącą zwolnij wierzchołek. 
void freeFU(struct FUNode *node) {
	if (node->indeg == 1) {
		if (node->rep != node) {
			freeFU(node->rep);
		}
		node->rep = NULL;
		free(node);
	} else {
		node->indeg--;
	}
}
