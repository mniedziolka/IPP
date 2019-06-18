#include <stdio.h>
#include <stdint.h>

#include "map.h"
#include "parser.h"

int32_t main() {
    int32_t i = 1;
    Map* map = newMap();

    while (getOneLine(map, i++));

    deleteMap(map);
    return 0;
}