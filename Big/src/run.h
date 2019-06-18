/** @file
 * Interfejs klasy wywołującej operacje.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#ifndef __RUN_H__
#define __RUN_H__

#include <stdint.h>

#include "map.h"

/** @brief Wypisuje informacje o błędzie.
 * Wypisuje na wyjście diagnostyczne numer linii oraz informację o błędzie.
 * @param [in] lineNo – numer linii w której wystąpił błąd;
 */
void callError(int32_t lineNo);

/** @brief Wykonuje dodanie drogi.
 * Sprawda podane parametry i wykonuje \ref addRoad().
 * Tworzy miasta, jeśli nie istnieją. Jeśli parametry są niepoprawne
 * wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeAddRoad(Map* map, int32_t lineNo,
                    uint32_t lastChar, const char* line);

/** @brief Wykonuje naprawę drogi.
 * Sprawda podane parametry i wykonuje \ref repairRoad().
 * Tworzy miasta, jeśli nie istnieją. Jeśli parametry są niepoprawne
 * wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeRepairRoad(Map* map, int32_t lineNo,
                       uint32_t lastChar, const char* line);

/** @brief Wykonuje wypisanie informacji o drodze krajowej.
 * Sprawda podane parametry i wykonuje \ref getRouteDescription().
 * Wypisuje wynik na standardowe wyjście.
 * Tworzy miasta, jeśli nie istnieją. Jeśli parametry są niepoprawne
 * wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeGetRouteDescription(Map* map, int32_t lineNo,
                                uint32_t lastChar, const char* line);

/** @brief Wykonuje dodanie konkretnej drogi krajowej.
 * Sprawda podane parametry i wykonuje \ref newCustomRoute().
 * Tworzy miasta, jeśli nie istnieją. Jeśli parametry są niepoprawne,
 * istnieją już drogi o późniejszej dacie budowy (lub ostatniej naprawy),
 * lub długość drogi jest inna niż podana wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeAddCustomRoute(Map* map, int32_t lineNo,
                           uint32_t lastChar, const char* line);

/** @brief Wykonuje wytyczenie i dodanie drogi krajowej.
 * Sprawda podane parametry i wykonuje \ref newRoute().
 * Jeśli parametry są niepoprawne, wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeNewRoute(Map* map, int32_t lineNo,
                     uint32_t lastChar, const char* line);

/** @brief Wykonuje wydłużenie podanej drogi krajowej.
 * Sprawda podane parametry i wykonuje \ref extendRoute().
 * Jeśli parametry są niepoprawne, wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeExtendRoute(Map* map, int32_t lineNo,
                        uint32_t lastChar, const char* line);

/** @brief Wykonuje usunięcie drogi.
 * Sprawda podane parametry i wykonuje \ref removeRoad().
 * Jeśli parametry są niepoprawne, wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeRemoveRoad(Map* map, int32_t lineNo,
                       uint32_t lastChar, const char* line);

/** @brief Wykonuje usunięcie drogi krajowej.
 * Sprawda podane parametry i wykonuje \ref removeRoute().
 * Jeśli parametry są niepoprawne, wywoła funkcję \ref callError().
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
void executeRemoveRoute(Map* map, int32_t lineNo,
                        uint32_t lastChar, const char* line);


#endif //__RUN_H__
