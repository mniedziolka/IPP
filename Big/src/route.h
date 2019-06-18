/** @file
 * Interfejs klasy przechowującej drogę krajową.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 29.04.2019
 */
#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <stdint.h>

#include "list.h"


/**
 * Struktura przechowująca pojedynczą drogę krajową.
 */
typedef struct Route {
    uint32_t id; ///< id drogi krajowej
    int32_t firstCityId; ///< id pierwszego miasta na drodze krajowej
    int32_t lastCityId; ///< id ostatniego miasta na drodze krajowej
    List* cities; ///< lista miast należących do drogi krajowej
} Route;

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p route.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] route – wskaźnik na usuwaną strukturę.
 */
void freeRoute(Route *route);

/** @brief Tworzy nową strukturę.
 * Tworzy nową, pustą strukturę, zawierającą id drogi krajowej,
 * i pustą listę wierzchołków należących do niej.
 * @param[in] routeId – id drogi krajowej;
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
Route* createRoute(uint32_t routeId);

/** @brief Znajduje drogę krajową.
 * Szuka określonej drogi krajowej na danej składowej.
 * @param [in,out] list – wskaźnik na początek listy;
 * @param[in] id        – id szukanej drogi krajowej;
 * @return Wartość @p true jeśli dane miasto należy do drogi krajowej.
 * Zwraca @p false w przeciwnym wypadku.
 */
bool existRoute(List* list, uint32_t id);

/** @brief Dodaje drogę krajową na wszystkie krawędzie.
 * Dla każdej kolejnej pary miast na liście znajduje krawędź między nimi.
 * Na znalezione krawędzie dodaje drogę krajową.
 * @param [in,out] list – wskaźnik na początek listy;
 * @param[in,out] route –  wskaźnik na drogę krajową;
 */
void addRouteOnEdges(List* list, Route* route);

/** @brief Dodaje drogę krajową do wszystkich miast.
 * Dla każdego miasta na liście dodaje drogę krajową.
 * @param [in,out] list – wskaźnik na początek listy;
 * @param[in,out] route –  wskaźnik na drogę krajową;
 */
void addRouteOnCities(List* list, Route* route);

/** @brief Sprawdza czy wybór drogi krajowej jest niejednoznaczny.
 * Iteruje się po wszystkich wierzchołkach na proponowanej drodze kraowej.
 * Sprawdza czy każdy został wybrany jednoznacznie.
 * @param [in,out] route – wskaźnik na początek listy zawierającej miasta;
 * @return Wartość @p true jeśli wybór drogi krajowej jest niejednoznaczny.
 * Wartość @p false w przeciwnym wypadku.
 */
bool isRouteAmbiguous(List* route);

/** @brief Usuwa drogę krajową ze wszystkich dostępnych struktur.
 * @param [in,out] route – wskaźnik na początek listy zawierającej miasta;
 */
void deleteRouteFromStructures(Route* route);

#endif //__ROUTE_H__
