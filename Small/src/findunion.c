#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "findunion.h"

struct FUNode *findRepresentative(struct FUNode *node) {
	if (node->rep != node) {
		node->rep = findRepresentative(node->rep);
	}

	return node->rep;
}

