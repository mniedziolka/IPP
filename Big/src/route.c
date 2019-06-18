/** @file
 * Implementacja route.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include "city.h"
#include "edge.h"
#include "route.h"


void freeRoute(Route *route) {
    if (route) {
        if (route->cities) {
            freeList(route->cities);
        }
        free(route);
    }
}


Route* createRoute(uint32_t routeId) {
    Route* route = malloc(sizeof(Route));

    if (route) {
        route->id = routeId;
        route->firstCityId = -1;
        route->lastCityId = -1;
        route->cities = NULL;
        return route;
    }

    return NULL;
}


bool existRoute(List* list, uint32_t id) {
    if (!list) {
        return false;
    }
    while (list->next) {
        Route* curr = list->data;
        if (curr->id == id) {
            return true;
        }
        list = list->next;
    }

    return false;
}


void addRouteOnEdges(List* list, Route* route) {
    List* first = list;
    List* second = list->next;

    while (second->next) {
        City* currCity = first->data;
        City* nextCity = second->data;

        Edge* currEdge = findEdge(currCity, nextCity);

        currEdge->route_ids =  listPushFront(&currEdge->route_ids, route);

        first = second;
        second = second->next;
    }
}


void addRouteOnCities(List* list, Route* route) {
    while (list->next) {
        City* currCity = list->data;
        currCity->belongRoutes = listPushFront(&currCity->belongRoutes, route);
        list = list->next;
    }
}


bool isRouteAmbiguous(List* route) {
    while (route && route->next) {
        City* node = route->data;
        if (node->unambiguous) {
            return true;
        }
        route = route->next;
    }

    return false;
}

/** Usuwa drogę krajową z podanej listy.
 * Iteruje się po liście, zwalnia wierzchołek z podaną drogą krajową,
 * przepina odpowiednio elementy by zachować ciągłość listy.
 *
 * @param[in,out] node  - wskaźnik na listę;
 * @param[in] routeId   - id usuwanej drogi krajowej;
 *
 */
static void deleteRouteFromSingleStructure(List* node, uint32_t routeId) {
    while (node->next && ((Route*)node->next->data)->id != routeId) {
        node = node->next;
    }

    if (node->next && ((Route*)node->next->data)->id == routeId) {
        List* deleteRoute = node->next;
        node->next = node->next->next;
        deleteRoute->next = NULL;
        freeList(deleteRoute);
    }
}


void deleteRouteFromStructures(Route* route) {
    List* cities = route->cities;
    while (cities->next) {
        City* currCity = cities->data;
        if (((Route*)currCity->belongRoutes->data)->id == route->id) {
            List* firstRoute = currCity->belongRoutes;
            currCity->belongRoutes = currCity->belongRoutes->next;
            firstRoute->next = NULL;
            freeList(firstRoute);
        } else {
            deleteRouteFromSingleStructure(currCity->belongRoutes, route->id);
        }

        if (cities->next->next) {
            City* nextCity = cities->next->data;
            Edge* edge = findEdge(currCity, nextCity);
            if (((Route*)edge->route_ids->data)->id == route->id) {
                List* firstRoute = edge->route_ids;
                edge->route_ids = edge->route_ids->next;
                firstRoute->next = NULL;
                freeList(firstRoute);
            } else {
                deleteRouteFromSingleStructure(edge->route_ids, route->id);
            }
        }


        cities = cities->next;
    }
}
