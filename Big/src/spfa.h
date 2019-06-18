/** @file
 * Interfejs klasy wykonującej bardziej zaawansowane
 * operacje na drogach krajowych.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 24.04.2019
 */

#ifndef __SPFA_H__
#define __SPFA_H__

#include "city.h"
#include "route.h"


/** @brief Szuka drogi krajowej.
 * Szuka najkrótszej ścieżki między dwoma miastami.
 * Używa algorytmu SPFA w którym kolejne wierzchołki do
 * sprawdzenia wrzucane są na stos.
 * @param [in] cityLength   – liczba miast;
 * @param [in,out] cityArr  – wskaźnik na tablicę miast;
 * @param [in,out] city1    – wskaźnik na nazwę miasta;
 * @param [in,out] city2    – wskaźnik na nazwę miasta;
 * @param [in] routeId      – id drogi krajowej;
 * @return Zwraca listę miast będących na drodze.
 * Jeśli @p city2 jest nieosiągalne z @p city1 zwraca NULL.
 * W przeciwnym razie listę z miastami leżącymi na drodze krajowej.
 */
List* getCitiesOnRoute(uint32_t cityLength, City** cityArr,
                       City* city1, City* city2, uint32_t routeId);

/** @brief Szuka drogi krajowej.
 * Szuka najkrótszej ścieżki między dwoma miastami.
 * Używa algorytmu SPFA w którym kolejne wierzchołki do
 * sprawdzenia wrzucane są na stos.
 * @param [in,out] route1  – lista wierzchołków na drodze;
 * @param [in,out] route2  – lista wierzchołków na drodze;
 * @return Zwraca 0 jeśli wybór jest niemożliwy.
 * Zwraca 1 jeśli opłaca się wybrać drogę pierwszą.
 * Zwraca 2 jeśli opłaca się wybrać drogę drugą.
 */
int8_t getBetterRoute(List *route1, List *route2);

#endif //__SPFA_H__
