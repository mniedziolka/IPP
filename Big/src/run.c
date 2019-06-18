/** @file
 * Implementacja run.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"
#include "edge.h"
#include "map.h"
#include "run.h"


void callError(int32_t lineNo) {
    fprintf(stderr, "ERROR %d\n", lineNo);
}

/** @brief Zwraca indeks następnego średnika.
 * Przeszukuje słowo od podanego miejsca startowego i zwraca indeks
 * pierwszego napotkanego średnika.
 * @param [in] lastChar  – indeks ostatniego znaku słowa;
 * @param [in] start     – indeks początkowego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 * @return Indeks pierwszego napotkanego średnika,
 * lub wartość @p lastChar jeśli do końca słowa nie ma żadnego średnika.
 */
static uint32_t getNextSemicolonId(uint32_t lastChar,
                                   uint32_t start, const char* line) {
    for (uint32_t i = start; i < lastChar; i++) {
        if (line[i] == ';') {
            return i;
        }
    }

    return lastChar;
}

/** @brief Sprawdza czy podane podsłowo może być poprawnym miastem.
 * Iteruje się od indeksu @p start do @p end.
 * Dla każdej litery sprawdza czy spełnia wymagania nazwy miasta.
 * @param [in] start     – indeks początkowego znaku;
 * @param [in] end       – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 * @return Wartość @p true jeśli podsłowo może być poprawnym miastem.
 * Wartość @p false w przeciwnym wypadku.
 */
static bool checkCity(uint32_t start, uint32_t end, const char* line) {
    for (uint32_t i = start; i < end; i++) {
        if (0 <= line[i] && line[i] <= 31) {
            return false;
        }
    }

    return start != end;
}

/** @brief Sprawdza czy podane podsłowo może być poprawną liczbą.
 * Iteruje się od indeksu @p start do @p end.
 * Dla każdego znaku sprawdza czy może on być poprawną liczbą.
 * Ponad to sprawdza czy liczba nie przekroczy zakresu.
 * @param [in] start     – indeks początkowego znaku;
 * @param [in] end       – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 * @param [in] unsign    – czy sprawdzana wartość jest typu unsigned;
 * @return Wartość @p true jeśli podsłowo może być poprawną liczbą.
 * Wartość @p false w przeciwnym wypadku.
 */
static bool checkInteger(uint32_t start, uint32_t end,
                         const char* line, bool unsign) {
    uint32_t checku = 0;
    int32_t checkd = 0;

    bool negative = false;

    for (uint32_t i = start; i < end; i++) {
        if (i == start && !unsign && line[i] == '-') {
            negative = true;
            continue;
        }
        if ('0' <= line[i] && line[i] <= '9') {
            if (unsign) {
                if ((UINT32_MAX - line[i] + '0') / 10 >= checku) {
                    checku = checku * 10 + line[i] - '0';
                } else {
                    return false;
                }
            } else {
                if (negative) {
                    if ((INT32_MIN + line[i] - '0') / 10 <= checkd) {
                        checkd = checkd * 10 - line[i] + '0';
                    } else {
                        return false;
                    }
                } else {
                    if ((INT32_MAX - line[i] + '0') / 10 >= checkd) {
                        checkd = checkd * 10 + line[i] - '0';
                    } else {
                        return false;
                    }
                }
            }
        } else {
            return false;
        }
    }


    return negative? start + 1 != end : start != end;
}


void executeAddRoad(Map* map, int32_t lineNo,
                    uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);
    size_t city1Length = end - start;
    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }
    size_t city2Length = end - start;

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    if (end == lastChar || !checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    if (end != lastChar || !checkInteger(start, end, line, false)) {
        callError(lineNo);
        return;
    }

    char* city1 = malloc((city1Length + 1) * sizeof(char));
    char* city2 = malloc((city2Length + 1) * sizeof(char));
    uint32_t length;
    int32_t builtYear;

    sscanf(line, "addRoad;%[^;];%[^;];%u;%d",
           city1, city2, &length, &builtYear);
    if (!addRoad(map, city1, city2, length, builtYear)) {
        callError(lineNo);
    }

    free(city1);
    free(city2);
}


void executeRepairRoad(Map* map, int32_t lineNo,
                       uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);
    size_t city1Length = end - start;
    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }
    size_t city2Length = end - start;

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    if (end != lastChar || !checkInteger(start, end, line, false)) {
        callError(lineNo);
        return;
    }


    char* city1 = malloc((city1Length + 1) * sizeof(char));
    char* city2 = malloc((city2Length + 1) * sizeof(char));
    int32_t builtYear = 0;

    sscanf(line, "repairRoad;%[^;];%[^;];%d", city1, city2, &builtYear);
    if (!repairRoad(map, city1, city2, builtYear)) {
        callError(lineNo);
    }

    free(city1);
    free(city2);
}


void executeGetRouteDescription(Map* map, int32_t lineNo,
                                uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);

    if (start == lastChar + 1 || end != lastChar ||
        !checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    uint32_t routeId;

    sscanf(line, "getRouteDescription;%u", &routeId);
    const char* result = getRouteDescription(map, routeId);

    if (result) {
        fprintf(stdout, "%s\n", result);
        free((char*)result);
    } else {
        callError(lineNo);
    }

}


void executeNewRoute(Map* map, int32_t lineNo,
                     uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);

    if (end == lastChar || !checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    size_t city1Length = end - start;

    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    size_t city2Length = end - start;

    if (end != lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    char* city1 = malloc((city1Length + 1) * sizeof(char));
    char* city2 = malloc((city2Length + 1) * sizeof(char));

    if (!city1 || !city2) {
        callError(lineNo);
        free(city1);
        free(city2);
        return;
    }

    uint32_t routeId = 0;
    sscanf(line, "newRoute;%d;%[^;];%s", &routeId, city1, city2);
    if (!newRoute(map, routeId, city1, city2)) {
        callError(lineNo);
    }

    free(city1);
    free(city2);
}


void executeExtendRoute(Map* map, int32_t lineNo,
                     uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);

    if (end == lastChar || !checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    size_t cityLength = end - start;

    if (end != lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    char* city = malloc((cityLength + 1) * sizeof(char));
    if (!city) {
        callError(lineNo);
        return;
    }

    uint32_t routeId;
    sscanf(line, "extendRoute;%d;%s", &routeId, city);
    if (!extendRoute(map, routeId, city)) {
        callError(lineNo);
    }

    free(city);
}


void executeRemoveRoad(Map* map, int32_t lineNo,
                     uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);
    size_t city1Length = end - start;

    if (end == lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    start = end + 1;
    end = getNextSemicolonId(lastChar, start, line);
    size_t city2Length = end - start;

    if (end != lastChar || !checkCity(start, end, line)) {
        callError(lineNo);
        return;
    }

    char* city1 = malloc((city1Length + 1) * sizeof(char));
    char* city2 = malloc((city2Length + 1) * sizeof(char));

    if (!city1 || !city2) {
        callError(lineNo);
        free(city1);
        free(city2);
        return;
    }

    sscanf(line, "removeRoad;%[^;];%s", city1, city2);

    if (!removeRoad(map, city1, city2)) {
        callError(lineNo);
    }

    free(city1);
    free(city2);
}


void executeRemoveRoute(Map* map, int32_t lineNo,
                     uint32_t lastChar, const char* line) {
    uint32_t start = getNextSemicolonId(lastChar, 0, line) + 1;
    uint32_t end = getNextSemicolonId(lastChar, start, line);

    if (end != lastChar || !checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    uint32_t routeId = 0;
    sscanf(line, "removeRoute;%u", &routeId);

    if (!removeRoute(map, routeId)) {
        callError(lineNo);
    }
}

/**
 * Struktura przechowująca krawędź z wejścia.
 */
typedef struct EdgeOnRoute {
    char* currCityName; ///< wskaźnik na nazwę aktualnego miasta
    char* nextCityName; ///< wskaźnik na nazwę następnego miasta
    uint32_t length; ///< długość drogi między miastami
    int32_t year; ///< rok budowy lub ostatniego remontu
} EdgeOnRoute;

/** @brief Zwalnia tablicę typu \ref EdgeOnRoute.
 * Iteruje się po tablicy elementów typu \ref EdgeOnRoute.
 * Zwalnia istniejące elementy.
 * @param [in] lastEdge   – liczba elementów w tablicy;
 * @param [in,out] array  – wskaźnik na początek tablicy,
 *                         która zawiera informacje o krawęðziach;
 */
static void freeEdgeOnRoute(uint32_t lastEdge, EdgeOnRoute** array) {
    for (uint32_t i = 0; i < lastEdge; i++) {
        free(array[i]->currCityName);
        free(array[i]->nextCityName);
        free(array[i]);
    }

    free(array);
}

/** @brief Zwalnia tablicę typu \ref EdgeOnRoute.
 * Iteruje się po tablicy elementów typu \ref EdgeOnRoute.
 * Zwalnia istniejące elementy.
 * @param [in,out] map   – wskaźnik na mapę;
 * @param [in,out] edge  – wskaźnik na początek tablicy,
 *                         która zawiera informacje o krawęðziach;
 */
static bool checkOneEdge(Map* map, EdgeOnRoute* edge) {
    if (edge->year == 0 || edge->length == 0) {
        return false;
    }

    City* city1 = findCity(map, edge->currCityName);
    City* city2 = findCity(map, edge->nextCityName);

    if (!city1 || !city2) {
        return true;
    }

    Edge* edgeOnMap = findEdge(city1, city2);

    if (edgeOnMap && edgeOnMap->active) {
        if (edge->year < edgeOnMap->year) {
            return false;
        } else {
            return edge->length == edgeOnMap->length;
        }
    } else {
        return true;
    }
}


void executeAddCustomRoute(Map* map, int32_t lineNo,
                           uint32_t lastChar, const char* line) {
    uint32_t start = 0;
    uint32_t end = getNextSemicolonId(lastChar, start, line);

    if (!checkInteger(start, end, line, true)) {
        callError(lineNo);
        return;
    }

    uint32_t routeId;
    sscanf(line, "%u;%*s", &routeId);

    if (routeId == 0 || 999 < routeId) {
        callError(lineNo);
        return;
    }

    if (findRoute(map, routeId)) {
        callError(lineNo);
        return;
    }

    size_t buff = 32;
    uint32_t lastEdge = 0;
    EdgeOnRoute** edgeCheck = malloc(buff * sizeof(EdgeOnRoute*));
    start = end + 1;

    bool oneCity = true;

    while (true) {
        uint32_t endCurrCity = getNextSemicolonId(lastChar, start, line);
        if (!checkCity(start, endCurrCity, line)) {
            callError(lineNo);
            freeEdgeOnRoute(lastEdge, edgeCheck);
            return;
        }
        if (endCurrCity == lastChar) {
            break;
        }

        uint32_t startLength = endCurrCity + 1;
        uint32_t endLength = getNextSemicolonId(lastChar, startLength, line);
        if (endCurrCity == lastChar ||
            !checkInteger(startLength, endLength, line, true)) {
            callError(lineNo);
            freeEdgeOnRoute(lastEdge, edgeCheck);
            return;
        }

        uint32_t startYear = endLength + 1;
        uint32_t endYear = getNextSemicolonId(lastChar, startYear, line);
        if (endYear == lastChar ||
            !checkInteger(startYear, endYear, line, false)) {
            callError(lineNo);
            freeEdgeOnRoute(lastEdge, edgeCheck);
            return;
        }

        uint32_t startNextCity = endYear + 1;
        end = getNextSemicolonId(lastChar, startNextCity, line);
        if (!checkCity(startNextCity, end, line)) {
            callError(lineNo);
            freeEdgeOnRoute(lastEdge, edgeCheck);
            return;
        }

        if (lastEdge == buff) {
            EdgeOnRoute** tmp = realloc(edgeCheck,
                                        buff * 2 * sizeof(EdgeOnRoute*));
            if (tmp) {
                buff *= 2;
                edgeCheck = tmp;
            } else {
                callError(lineNo);
                freeEdgeOnRoute(lastEdge, edgeCheck);
                return;
            }
        }

        edgeCheck[lastEdge] = malloc(sizeof(EdgeOnRoute));
        edgeCheck[lastEdge]->currCityName = malloc(
                (endCurrCity - start + 1) * sizeof(char)
        );
        edgeCheck[lastEdge]->nextCityName = malloc(
                (end - startNextCity + 1) * sizeof(char)
        );

        sscanf(&line[start], "%[^;];%u;%d;%[^;]",
                edgeCheck[lastEdge]->currCityName,
                &edgeCheck[lastEdge]->length,
                &edgeCheck[lastEdge]->year,
                edgeCheck[lastEdge]->nextCityName
        );

        if (!checkOneEdge(map, edgeCheck[lastEdge])) {
            callError(lineNo);
            lastEdge++;
            freeEdgeOnRoute(lastEdge, edgeCheck);
            return;
        }



        for (uint32_t i = 0; i <= lastEdge; i++) {
            if (strcmp(edgeCheck[i]->currCityName,
                       edgeCheck[lastEdge]->nextCityName) == 0) {
                callError(lineNo);
                freeEdgeOnRoute(lastEdge+1, edgeCheck);
                return;
            }
        }
        oneCity = false;
        start = startNextCity;
        lastEdge++;
    }

    if (oneCity) {
        callError(lineNo);
        freeEdgeOnRoute(lastEdge, edgeCheck);
        return;
    }

    for (uint32_t i = 0; i < lastEdge; i++) {
        if (!addRoad(
                map,
                edgeCheck[i]->currCityName,
                edgeCheck[i]->nextCityName,
                edgeCheck[i]->length,
                edgeCheck[i]->year
            )) {
            repairRoad(map, edgeCheck[i]->currCityName,
                       edgeCheck[i]->nextCityName, edgeCheck[i]->year);
        }
    }

    List* citiesOnRoute = newList();
    for (int32_t i = lastEdge - 1; i >= 0; i--) {
        citiesOnRoute = listPushFront(&citiesOnRoute,
                                      findCity(map, edgeCheck[i]->nextCityName));
    }
    citiesOnRoute = listPushFront(&citiesOnRoute,
                                  findCity(map, edgeCheck[0]->currCityName));
    newCustomRoute(map, routeId, citiesOnRoute);
    freeEdgeOnRoute(lastEdge, edgeCheck);
}
