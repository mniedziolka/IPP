/** @file
 * Interfejs klasy wykonującej wczytanie danych i wstępne sprawdzenie.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdbool.h>
#include <stdint.h>

#include "map.h"

/** @brief Wczytuje jedną linię.
 * Wczytuje jedną linię tekstu ze standardowego wejścia.
 * Sprawdza czy nie został napotkany znak końca pliku.
 * Jeśli koniec pliku nastąpił w innym miejscu niż zaraz po znaku
 * końca linii, wywoła \ref callError().
 * @param[in,out] map – wskaźnik na mapę;
 * @param[in] lineNo  – numer linii;
 * @return Wartość @p true, jeśli linia została wczytana poprawnie.
 * Wartość @p false, jeśli został napotkany koniec pliku.
 */
bool getOneLine(Map* map, int32_t lineNo);

#endif //__PARSER_H__
