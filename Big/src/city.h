/** @file
 * Interfejs klasy przechowującej miasto
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 24.04.2019
 */

#ifndef __CITY_H__
#define __CITY_H__

#include <stdbool.h>
#include <stdint.h>

#include "list.h"
#include "route.h"

/**
 * Struktura przechowująca miasto.
 */
typedef struct City {
    int32_t id;  ///< id miasta
    uint64_t distance; ///< odległość do miasta
    int32_t minMaxYear; ///< najstarsza droga na mapie
    int32_t lastId; ///< id miasta z którego SPFA weszło do wierzchołka
    bool unambiguous; ///< czy miasto zostało wybrane niejednoznacznie
    char* cityName; ///< wskaźnik na nazwę miasta
    List* neighbors; ///< lista sąsiedztwa (krawędzi
    List* belongRoutes; ///< lista dróg krajowych przechodzących przez miasto
} City;

/** @brief Tworzy nową strukturę.
 * Tworzy nową, pustą strukturę, zawierającą nazwę miasta,
 * pustą listę sąsiadów i pustą listę dróg krajowych.
 * @param[in,out] cityName – wskaźnik na nazwę miasta;
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
City* newCity(const char *cityName);

/** @brief Sprawdza poprawność nazwy miasta.
 * Sprawdza, czy w nazwie miasta nie ma znaków z zakresu [0, 31],
 * lub średnika.
 * @param[in,out] cityName – wskaźnik na nazwę miasta;
 * @return Wartość @p true, jeśli nazwa miasta jest poprawna.
 * Wartość @p false, w przeciwnym wypadku.
 */
bool cityCorrect(const char* cityName);

/** @brief Zwalnia miasto z pamięci.
 * Zwalnia z pamięci wszystkie struktury należące do miasta.
 * Na koniec zwalnia miasto.
 * @param[in,out] city – wskaźnik na miasto;
 */
void freeCity(City *city);

#endif //__CITY_H__
