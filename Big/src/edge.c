/** @file
 * Implementacja edge.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <string.h>

#include "city.h"
#include "edge.h"


void freeEdge(Edge* edge) {
    freeList(edge->route_ids);
    free(edge);
}

/** @brief Tworzy nową krawędź.
 * Alokuje pamięć i przypisuje zmienne do nowej krawędzi.
 *
 * @param[in] targetCityId - indeks miasta na który krawędź ma wskazywać;
 * @param[in] length       - długość krawędzi;
 * @param[in] year         - rok powstania krawędzi
 *
 * @return Wskaźnik na nowo utworzoną krawęðź.
 * NULL jeśli nie udało się zalokować pamięci.
 */
static Edge* newEdge(uint32_t targetCityId, uint32_t length, int32_t year) {
    Edge *edge = malloc(sizeof(Edge));

    if (edge) {
        edge->length = length;
        edge->year = year;
        edge->route_ids = newList();
        edge->targetCityId = targetCityId;
        edge->active = true;
    }

    return edge;
}


Edge *findEdge(City *city1, City *city2) {
    List *node = city1->neighbors;

    while (node->next) {
        Edge *currEdge = node->data;
        if (city2->id == currEdge->targetCityId) {
            return currEdge;
        }

        node = node->next;
    }

    return NULL;
}


bool addEdge(City *city1, City *city2, uint32_t length, int32_t builtYear) {
    Edge* edge = findEdge(city1, city2);
    if (edge) {
        if (edge->active) {
            return false;
        } else {
            edge->active = true;
            edge->length = length;
            edge->year = builtYear;
            freeList(edge->route_ids);
            edge->route_ids = newList();
            return true;
        }
    }

    edge = newEdge(city2->id, length, builtYear);
    if (edge) {
        city1->neighbors = listPushFront(&city1->neighbors, edge);
        return true;
    } else {
        return false;
    }
}


bool updateRoadYear(City *city1, City *city2, int32_t year) {
    if (year == 0) {
        return false;
    }
    Edge *tmp = findEdge(city1, city2);
    if (tmp && tmp->active && tmp->year <= year) {
        tmp->year = year;
    } else {
        return false;
    }

    tmp = findEdge(city2, city1);
    if (tmp && tmp->active && tmp->year <= year) {
        tmp->year = year;
    } else {
        return false;
    }

    return true;
}