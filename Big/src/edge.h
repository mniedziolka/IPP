/** @file
 * Interfejs klasy przechowującej pojedynczą krawędź.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 29.04.2019
 */

#ifndef __EDGE_H__
#define __EDGE_H__

#include <stdbool.h>
#include <stdint.h>

#include "city.h"
#include "list.h"

/**
 * Struktura przechowująca pojedynczą krawędź.
 */
typedef struct Edge {
    uint32_t length; ///< długość krawędzi
    int32_t year; ///< rok budowy lub remontu
    int32_t targetCityId; ///< miasto na które krawędź wskazuje
    List* route_ids; ///< lista dróg krajowych do których należy krawędź
    bool active; ///< czy droga jest aktywna
} Edge;

/** @brief Zwalnia krawędź z pamięci.
 * Zwalnia z pamięci wszystkie struktury należące do krawędzi.
 * Na koniec zwalnia krawędź.
 * @param[in,out] edge – wskaźnik na krawędź;
 */
void freeEdge(Edge* edge);

/** @brief Znajduje pojedynczą krawędź
 * Szuka krawędzi pomiędzy dwoma miastami.
 * Miasta muszą istnieć.
 * @param[in, out] city1 – wskaźnik na miasto
 * @param[in, out] city2 – wskaźnik na miasto
 * @return Wskaźnik na znalezioną krawędź lub NULL,
 * gdy szukana krawędź nie istnieje.
 */
Edge *findEdge(City *city1, City *city2);

/** @brief Dodaje krawędź między miastami.
 * Tworzy nową krawędź między podanymi miastami.
 * Miasta muszą istnieć.
 * @param[in, out] city1 – wskaźnik na miasto
 * @param[in, out] city2 – wskaźnik na miasto
 * @param[in] length     – długość drogi
 * @param[in] builtYear  – rok budowy lub ostatniego remontu
 * @return Zwraca @p true, jeśli krawędź została utworzona poprawnie.
 * Zwraca @p false, jeśli któryś z parametrów jest niewłaściwy,
 * lub nie udało się zalokować pamięci.
 */
bool addEdge(City *city1, City *city2, uint32_t length, int32_t builtYear);

/** @brief Uaktualnia datę krawędzi.
 * Uaktualnia datę budowy lub datę ostatniego remontu drogi.
 * @param[in,out] city1 – wskaźnik na miasto
 * @param[in,out] city2 – wskaźnik na miasto
 * @param[in] year  – rok budowy lub ostatniego remontu
 * @return Zwraca @p true, jeśli udało się zaktualizować datę.
 * Zwraca @p false, jeśli któryś z parametrów jest niewłaściwy,
 * lub podana krawędź nie istnieje.
 */
bool updateRoadYear(City *city1, City *city2, int32_t year);

#endif //__EDGE_H__
