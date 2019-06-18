/** @file
 * Implementacja city.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "edge.h"


bool cityCorrect(const char* cityName) {
    uint32_t length = 0;
    while (*cityName != '\0') {
        if ((0 < *cityName && *cityName < 32) || *cityName == ';') {
            return false;
        }
        length++;
        cityName++;
    }

    return length > 0;
}


City* newCity(const char *cityName) {
    City *city = malloc(sizeof(City));

    if (city) {
        size_t n = strlen(cityName) + 1;
        city->cityName = malloc(n * sizeof(char));
        if (!city->cityName) {
            free(city);
            return NULL;
        }
        strcpy(city->cityName, cityName);
        city->neighbors = newList();
        city->belongRoutes = newList();
    }

    return city;
}


void freeCity(City *city) {
    List* edgeList = city->neighbors;
    while (edgeList->next) {
        Edge* edge = edgeList->data;
        freeEdge(edge);
        edgeList = edgeList->next;
    }
    freeList(city->neighbors);
    if (city->belongRoutes) {
        freeList(city->belongRoutes);
    }
    free(city->cityName);
    free(city);
}
