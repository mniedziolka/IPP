#include <string.h>

#include "spfa.h"
#include "edge.h"
#include "map.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


List* getCitiesOnRoute(uint32_t cityLength, City** cityArr,
                       City* city1, City* city2, uint32_t routeId) {
    List* result = newList();
    List* stack = newList();

    if (!result || !stack) {
        return NULL;
    }

    for (uint32_t i = 0; i < cityLength; i++) {
        City *curr = cityArr[i];
        curr->distance = UINT64_MAX;
        curr->minMaxYear = INT32_MIN;
        curr->lastId = -1;
        curr->unambiguous = false;
    }

    city1->distance = 0;
    city1->minMaxYear = INT32_MAX;
    city1->lastId = city1->id;

    stack = listPushFront(&stack, city1);

    while (stack->next) {
        City* curr = getLast(stack)->data;
        popLast(stack);

        if (curr->id == city2->id) {
            continue;
        }

        List* node = curr->neighbors;
        while (node->next) {
            Edge* edge = node->data;
            if (!edge->active) {
                node = node->next;
                continue;
            }

            City* city = cityArr[edge->targetCityId];
            if (existRoute(city->belongRoutes, routeId) ) {
                if (city->id != city2->id) {
                    node = node->next;
                    continue;
                }

            }

            if ((city->distance > curr->distance + edge->length)
                || (city->distance == curr->distance + edge->length
                && city->minMaxYear < MIN(curr->minMaxYear, edge->year))) {

                city->distance = curr->distance + edge->length;
                city->minMaxYear = MIN(curr->minMaxYear, edge->year);
                city->lastId = curr->id;
                city->unambiguous = false;

                stack = listPushFront(&stack, cityArr[edge->targetCityId]);
            } else if (city->distance == curr->distance + edge->length &&
                       city->minMaxYear == MIN(curr->minMaxYear, edge->year)) {
                city->unambiguous = true;
            }

            node = node->next;
        }
    }

    City* node = city2;
    if (city2->distance == UINT64_MAX) {
        freeList(stack);
        freeList(result);
        return NULL;
    }
    result = listPushFront(&result, cityArr[node->id]);
    while (node->lastId != city1->id) {
        if (node->unambiguous) {
            freeList(stack);
            freeList(result);
            return NULL;
        }
        result = listPushFront(&result, cityArr[node->lastId]);
        node = cityArr[node->lastId];
    }
    if (cityArr[node->lastId]->unambiguous) {
        freeList(stack);
        freeList(result);
        return NULL;
    }
    result = listPushFront(&result, cityArr[node->lastId]);

    freeList(stack);

    return result;
}


int8_t getBetterRoute(List* route1, List* route2) {
    if (!route1 && !route2) {
        return 0;
    }

    uint64_t length1 = 0, length2 = 0;
    int32_t year1 = INT32_MAX, year2 = INT32_MAX;
    bool firstAmbiguous = false;
    bool secondAmbiguous = false;

    if (route1) {
        firstAmbiguous = isRouteAmbiguous(route1);
    } else {
        length1 = UINT64_MAX;
        year1 = INT32_MIN;
    }

    if (route2) {
        secondAmbiguous = isRouteAmbiguous(route2);
    } else {
        length2 = UINT64_MAX;
        year2 = INT32_MIN;
    }

    if (firstAmbiguous) {
        length1 = UINT64_MAX;
        year1 = INT32_MIN;
    }

    if (secondAmbiguous) {
        length2 = UINT64_MAX;
        year2 = INT32_MIN;
    }

    if (firstAmbiguous && secondAmbiguous) {
        freeList(route1);
        freeList(route2);
        return 0;
    }

    List* node = route1;
    if (route1 && !firstAmbiguous && node->next) {
        while (node->next->next) {
            City *currCity = node->data;
            City *nextCity = node->next->data;
            Edge *currEdge = findEdge(currCity, nextCity);

            length1 += currEdge->length;
            year1 = MIN(year1, currEdge->year);

            node = node->next;
        }
    }


    node = route2;
    if (route2 && !secondAmbiguous && node->next) {
        while (node->next->next) {
            City *currCity = node->data;
            City *nextCity = node->next->data;
            Edge *currEdge = findEdge(currCity, nextCity);

            length2 += currEdge->length;
            year2 = MIN(year2, currEdge->year);

            node = node->next;
        }
    }


    if (length1 < length2) {
        if (route2) {
            freeList(route2);
        }
        return 1;
    } else if (length1 == length2 && year1 <= year2) {
        if (year1 == year2) {
            if (route1) {
                freeList(route1);
            }
            if (route2) {
                freeList(route2);
            }
            return 0;
        } else {
            if (route1) {
                freeList(route1);
            }
            return 2;
        }
    } else {
        if (route1) {
            freeList(route1);
        }
        return 2;
    }
}