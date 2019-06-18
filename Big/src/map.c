/** @file
 * Implementacja map.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spfa.h"
#include "edge.h"
#include "map.h"
#include "list.h"

/**
 * Struktura przechowująca mapę dróg krajowych.
 */
typedef struct Map {
    size_t cityBuff; ///< rozmiar zalokowanej pamięci na miasta
    size_t routeBuff; ///< rozmiar zalokowanej pamięci na drogi krajowe
    uint32_t lastCity; ///< indeks zaostatniego miasta
    uint32_t lastRoute; ///< indeks zaostatniej drogi krajowej
    City **city; ///< tablica miast
    Route **route; ///< tablica dróg krajowych
} Map;


Map* newMap(void) {
    Map *map = malloc(sizeof(Map));
    if (map) {
        map->cityBuff = 32;
        map->lastCity = 0;

        map->city = malloc(map->cityBuff * sizeof(City*));

        map->routeBuff = 8;
        map->lastRoute = 0;
        map->route = malloc(map->routeBuff * sizeof(Route*));
    }

    return map;
}


void deleteMap(Map *map) {
    if (map) {
        for (uint32_t i = 0; i < map->lastCity; i++) {
            freeCity(map->city[i]);
        }
        free(map->city);

        for (uint32_t i = 0; i < map->lastRoute; i++) {
            freeRoute(map->route[i]);
        }
        free(map->route);

        free(map);
    }
}


City* findCity(Map* map, const char *city) {
    for (uint32_t i = 0; i < map->lastCity; i++) {
        if (strcmp(city, map->city[i]->cityName) == 0) {
            return map->city[i];
        }
    }

    return NULL;
}


Route* findRoute(Map* map, uint32_t routeId) {
    for (uint32_t i = 0; i < map->lastRoute; i++) {
        if (map->route[i]->id == routeId) {
            return map->route[i];
        }
    }

    return NULL;
}

/** @brief Dodaje miasto do mapy.
 * Dodaje miasto o podanej nazwie do mapy.
 * @param[in,out] map  – wskaźnik na mapę;
 * @param[in,out] city – wskaźnik na nazwę miasta;
 * @return Zwraca wskaźnik na dodane miasto.
 * Jeśli alokacja lub realokacja nie powiodła się zwraca NULL.
 */
City* addCityToMap(Map *map, const char *city) {
    if (map->lastCity == map->cityBuff) {
        uint32_t tmpSize = 2 * map->cityBuff;
        City** tmp = realloc(map->city, tmpSize * sizeof(City*));
        if (tmp) {
            map->city = tmp;
            map->cityBuff = tmpSize;
        } else {
            return NULL;
        }
    }
    map->city[map->lastCity] = newCity(city);
    if (!map->city[map->lastCity]) {
        return NULL;
    }
    map->city[map->lastCity]->id = map->lastCity;
    return map->city[map->lastCity++];
}


bool addRoad(Map *map, const char *city1, const char *city2,
             uint32_t length, int32_t builtYear) {

    if (!map || !cityCorrect(city1)
        || !cityCorrect(city2) || strcmp(city1, city2) == 0) {
        return false;
    }

    if (length == 0 || builtYear == 0) {
        return false;
    }

    City *firstCity = findCity(map, city1);
    City *secondCity = findCity(map, city2);

    if (!firstCity) {
        firstCity = addCityToMap(map, city1);
        if (!firstCity) {
            return false;
        }
    }

    if (!secondCity) {
        secondCity = addCityToMap(map, city2);
        if (!secondCity) {
            map->lastCity--;
            freeCity(map->city[map->lastCity]);
            return false;
        }
    }


    return addEdge(firstCity, secondCity, length, builtYear)
           && addEdge(secondCity, firstCity, length, builtYear);
}


bool repairRoad(Map *map, const char *city1,
                const char *city2, int32_t repairYear) {
    if (!map || !cityCorrect(city1) || !cityCorrect(city2)) {
        return false;
    }

    City *firstCity = findCity(map, city1);
    City *secondCity = findCity(map, city2);

    if (!firstCity || !secondCity) {
        return false;
    }

    return updateRoadYear(firstCity, secondCity, repairYear);
}


bool newRoute(Map *map, uint32_t routeId,
              const char *city1, const char *city2) {
    if (!map || !cityCorrect(city1) || !cityCorrect(city2)) {
        return false;
    }

    if (routeId < 1 || 999 < routeId) {
        return false;
    }

    if (findRoute(map, routeId)) {
        return false;
    }

    City* firstCity = findCity(map, city1);
    City* secondCity = findCity(map, city2);

    if (!firstCity || !secondCity || firstCity == secondCity) {
        return false;
    }

    if (map->lastRoute == map->routeBuff) {
        size_t tmpSize = map->routeBuff * 2;
        Route** newRouteArr = realloc(map->route, tmpSize * sizeof(Route*));
        if (newRouteArr) {
            map->route = newRouteArr;
            map->routeBuff = tmpSize;
        } else {
            return false;
        }
    }

    map->route[map->lastRoute] = createRoute(routeId);
    Route* currRoute = map->route[map->lastRoute];
    if (!currRoute) {
        return false;
    }

    currRoute->cities = getCitiesOnRoute(map->lastCity, map->city,
                                         firstCity, secondCity, routeId);

    if (!currRoute->cities) {
        freeRoute(map->route[map->lastRoute]);
        return false;
    }

    if (isRouteAmbiguous(currRoute->cities)) {
        freeList(currRoute->cities);
        currRoute->cities = NULL;
    }

    List* path = currRoute->cities;

    City* currCity = path->data;
    currRoute->firstCityId = currCity->id;

    addRouteOnEdges(path, map->route[map->lastRoute]);

    addRouteOnCities(path, map->route[map->lastRoute]);


    currRoute->lastCityId = ((City*)getLast(path)->data)->id;
    map->lastRoute++;

    return true;
}


bool newCustomRoute(Map* map, uint32_t routeId, List* citiesOnRoute) {
    if (!map || routeId < 1 || 999 < routeId) {
        return false;
    }

    if (findRoute(map, routeId)) {
        return false;
    }

    if (map->lastRoute == map->routeBuff) {
        size_t tmpSize = map->routeBuff * 2;
        Route** newRouteArr = realloc(map->route, tmpSize * sizeof(Route*));
        if (newRouteArr) {
            map->route = newRouteArr;
            map->routeBuff = tmpSize;
        } else {
            return false;
        }
    }
    map->route[map->lastRoute] = createRoute(routeId);
    Route* currRoute = map->route[map->lastRoute];

    currRoute->cities = citiesOnRoute;
    currRoute->firstCityId = ((City*)citiesOnRoute->data)->id;
    currRoute->lastCityId = ((City*)getLast(citiesOnRoute)->data)->id;

    addRouteOnEdges(citiesOnRoute, currRoute);

    addRouteOnCities(citiesOnRoute, currRoute);

    map->lastRoute++;
    return true;
}


bool extendRoute(Map *map, uint32_t routeId, const char *city) {
    if (!map || !cityCorrect(city)) {
        return false;
    }

    Route* route = findRoute(map, routeId);
    if (!route) {
        return false;
    }

    City* currCity = findCity(map, city);

    if (!currCity || currCity->id == route->lastCityId
        || currCity->id == route->firstCityId) {
        return false;
    }

    List* node = currCity->belongRoutes;
    while (node->next) {
        Route* currRoute = node->data;
        if (currRoute->id == routeId) {
            return false;
        }

        node = node->next;
    }

    City* beginCity = map->city[route->firstCityId];
    City* endCity = map->city[route->lastCityId];

    List* toFirst = getCitiesOnRoute(map->lastCity, map->city,
                                     currCity, beginCity, routeId);
    List* fromSecond = getCitiesOnRoute(map->lastCity, map->city,
                                        endCity, currCity, routeId);


    uint8_t result = getBetterRoute(toFirst, fromSecond);

    switch (result) {
        case 0:
            return false;
        case 1:
            addRouteOnEdges(toFirst, route);

            List* withoutLast = copyList(toFirst);
            popLast(withoutLast);
            addRouteOnCities(withoutLast, route);
            freeList(withoutLast);

            List* last = getLast(toFirst);
            freeList(last->next);
            last->next = route->cities->next;
            route->cities = last->next;
            break;
        case 2:
            addRouteOnEdges(fromSecond, route);
            addRouteOnCities(fromSecond->next, route);
            last = getLast(route->cities);
            freeList(last->next);
            last->next = fromSecond->next;
            free(fromSecond);
            break;
    }

    return true;
}

/** @brief Zwalnia tablicę list.
 * Zwalnia listy, na które wskaźniki trzymane są w tablicy.
 * Na koniec zwalnia tablicę.
 *
 * @param[in] end         – indeks ostatniego elementu;
 * @param[in,out] toFree  – wskaźnik na tablicę list;
 */
static void freeArrayOfList(uint32_t end, List** toFree) {
    for (uint32_t i = 0; i < end; i++) {
        freeList(toFree[i]);
    }
    free(toFree);
}

/** @brief Szuka miasta na drodze krajowej.
 * Przeszukuje zadaną drogę krajową i znajduje podane miasto.
 *
 * @param[in,out] route – wskaźnik na drogę krajową;
 * @param[in,out] city  – wskaźnik na szukane miasto;
 *
 * @return Wskaźnik na element listy zawierający podane miasto.
 * Wartość NULL w przeciwnym przypadku.
 */
static List* searchCityInRoute(Route* route, City* city) {
    List* node = route->cities;
    while (node->next) {
        City* currCity = node->data;
        if (currCity->id == city->id) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

bool removeRoad(Map *map, const char *city1, const char *city2) {
    if (!map || !cityCorrect(city1) || !cityCorrect(city2)) {
        return false;
    }

    City *beginCity = findCity(map, city1);
    City *endCity = findCity(map, city2);

    if (!beginCity || !endCity) {
        return false;
    }

    Edge* fedge = findEdge(beginCity, endCity);
    Edge* sedge = findEdge(endCity, beginCity);

    if (!fedge || !sedge || !fedge->active || !sedge->active) {
        return false;
    }

    fedge->active = false;
    sedge->active = false;


    bool check = true;
    size_t sizeNewRoutes = 32;
    uint32_t lastNewRoute = 0;
    List **arrNewRoutes = malloc(sizeNewRoutes * sizeof(List *));
    if (!arrNewRoutes) {
        check = false;
    }
    for (uint32_t i = 0; i < 2; i++) {
        Edge *eraseEdge = findEdge(beginCity, endCity);

        List *currRoute = eraseEdge->route_ids;

        while (check && currRoute->next) {
            if (lastNewRoute == sizeNewRoutes) {
                sizeNewRoutes *= 2;
                List** tmp = realloc(arrNewRoutes, sizeNewRoutes * sizeof(List*));
                if (tmp) {
                    arrNewRoutes = tmp;
                } else {
                    freeArrayOfList(lastNewRoute, arrNewRoutes);
                }
            }
            Route *route = currRoute->data;


            List *result = getCitiesOnRoute(map->lastCity, map->city,
                                            beginCity, endCity, route->id);

            if (!result) {
                check = false;
                break;
            }

            arrNewRoutes[lastNewRoute] = result;

            lastNewRoute++;
            currRoute = currRoute->next;
        }

        City* tmpCity = beginCity;
        beginCity = endCity;
        endCity = tmpCity;
    }

    if (check) {
        City* tmpCity = beginCity;
        beginCity = endCity;
        endCity = tmpCity;
        uint32_t it = 0;
        for (uint32_t i = 0; i < 2; i++) {
            Edge* eraseEdge = findEdge(beginCity, endCity);
            List* routes = eraseEdge->route_ids;

            while (routes->next) {
                List* currCity = searchCityInRoute(routes->data, beginCity);

                addRouteOnEdges(arrNewRoutes[it], routes->data);

                List* withoutLast = copyList(arrNewRoutes[it]);
                popLast(withoutLast);
                addRouteOnCities(withoutLast->next, routes->data);
                freeList(withoutLast);

                List* nextCity = currCity->next;
                currCity->next = arrNewRoutes[it]->next;
                arrNewRoutes[it]->next = NULL;
                freeList(arrNewRoutes[it]);

                List* last = getLast(currCity->next);
                freeList(last->next);
                last->next = nextCity->next;
                nextCity->next = NULL;
                freeList(nextCity);

                it++;
                routes = routes->next;
            }

            tmpCity = beginCity;
            beginCity = endCity;
            endCity = tmpCity;
        }

        free(arrNewRoutes);
        return true;
    } else {
        for (uint32_t i = 0; i < 2; i++) {
            Edge* eraseEdge = findEdge(beginCity, endCity);
            eraseEdge->active = true;
            City* tmpCity = beginCity;
            beginCity = endCity;
            endCity = tmpCity;
        }

        return false;
    }

}

char const* getRouteDescription(Map *map, uint32_t routeId) {
    char* str = malloc(sizeof(char));
    if (!str) {
        return NULL;
    }
    *str = '\0';
    if (!map || routeId == 0 || routeId > 999) {
        return str;
    }

    Route* route = findRoute(map, routeId);

    if (!route) {
        return str;
    }

    size_t size = 32;
    uint32_t last = 0;
    free(str);
    str = malloc(size * sizeof(char));

    if (str) {
        last = sprintf(str, "%u;", routeId);
        List* list = route->cities;
        while (list->next->next) {
            City* city1 = list->data;
            City* city2 = list->next->data;

            size_t nameLength = strlen(city1->cityName);

            if (last + nameLength > size / 2) {
                size += nameLength;
                size *= 2;
                char* tmp = realloc(str, size * sizeof(char));
                if (!tmp) {
                    free(str);
                    str = malloc(sizeof(char));
                    *str = '\0';
                    return str;
                }

                str = tmp;
            }

            strcat(str, city1->cityName);
            strcat(str, ";");

            last += nameLength + 1;
            Edge* currEdge = findEdge(city1, city2);

            char tmp[64];
            uint32_t paramsLength = sprintf(tmp, "%u;%d;",
                                            currEdge->length, currEdge->year);
            strcat(str, tmp);
            last += paramsLength;

            list = list->next;
        }

        size_t nameLength = strlen(((City*)(list->data))->cityName);
        if (last + nameLength > size / 2) {
            size += nameLength;
            size *= 2;
            char* tmp = realloc(str, size * sizeof(char));
            if (!tmp) {
                free(str);
                str = malloc(sizeof(char));
                *str = '\0';
                return str;
            }

            str = tmp;
        }
        strcat(str, ((City*)(list->data))->cityName);
    }

    return str;
}


bool removeRoute(Map* map, uint32_t routeId) {
    uint32_t routeInArr = map->lastRoute;
    for (uint32_t i = 0; i < map->lastRoute; i++) {
        if (map->route[i]->id == routeId) {
            routeInArr = i;
        }
    }

    if (routeInArr == map->lastRoute) {
        return false;
    }

    deleteRouteFromStructures(map->route[routeInArr]);

    if (map->lastRoute != 0) {
        Route* routeToRemove = map->route[routeInArr];
        freeRoute(routeToRemove);
        map->route[routeInArr] = map->route[--map->lastRoute];

    }

    map->route[map->lastRoute] = NULL;


    return true;
}
