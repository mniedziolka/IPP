/** @file
 * Interfejs klasy wywołującej operacje.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "run.h"

/** @brief Wczytuje niepotrzebne znaki ze standardowego wejścia.
 * Wczytuje znaki ze standardowego wejścia do napotkania końca linii,
 * lub końca pliku.
 * @return Wartość @p true jeśli napotkano znak końca linii.
 * Wartość @p false jeśli napotkano koniec pliku.
 */
static bool readGarbage() {
    int32_t garbage = getchar();

    while (garbage != '\n') {
        if (garbage == -1) {
            return false;
        }
        garbage = getchar();
    }

    return true;
}

/** @brief Wykonuje polecenie z linii.
 * Sprawdza czy komenda pasuje do zadanego zbioru komend,
 * po czym wykonuje odpowiednie polecenie.
 * @param [in,out] map   – wskaźnik na mapę do której ma zostać dodana droga;
 * @param [in] lineNo    – numer linii z której zostały pobrane dane;
 * @param [in] lastChar  – indeks ostatniego znaku;
 * @param [in,out] line  – wskaźnik na początek słowa,
 *                         które zawiera informacje o tworzonej drodze;
 */
static bool executeLine(Map* map, int32_t lineNo,uint32_t lastChar, char* line) {
    char* command[] = {
            "addRoad",
            "repairRoad",
            "getRouteDescription",
            "newRoute",
            "extendRoute",
            "removeRoad",
            "removeRoute"
    };

    uint8_t cmd = 7;
    for (uint32_t i = 0; i < 7; i++) {
        bool check = true;
        size_t currCommandLength = strlen(command[i]);
        for (uint32_t j = 0; j < currCommandLength; j++) {
            if (command[i][j] != line[j]) {
                check = false;
                break;
            }
        }

        if (check) {
            cmd = i;
            break;
        }
    }

    switch (cmd) {
        case 0:
            executeAddRoad(map, lineNo, lastChar, line);
            break;
        case 1:
            executeRepairRoad(map, lineNo, lastChar, line);
            break;
        case 2:
            executeGetRouteDescription(map, lineNo, lastChar, line);
            break;
        case 3:
            executeNewRoute(map, lineNo, lastChar, line);
            break;
        case 4:
            executeExtendRoute(map, lineNo, lastChar, line);
            break;
        case 5:
            executeRemoveRoad(map, lineNo, lastChar, line);
            break;
        case 6:
            executeRemoveRoute(map, lineNo, lastChar, line);
            break;
        default:
            executeAddCustomRoute(map, lineNo, lastChar, line);
            break;
    }

    return true;
}


bool getOneLine(Map* map, int32_t lineNo) {
    size_t sizeLine = 64;
    uint32_t lastChar = 0;
    char* line = malloc(sizeLine * sizeof(char));

    int32_t currChar = getchar();
    if (currChar == -1) {
        free(line);
        return false;
    }
    if (currChar == '#') {
        free(line);
        return readGarbage();
    }

    if (currChar == '\n') {
        free(line);
        return true;
    }

    while (currChar != '\n') {
        if (lastChar + 1 == sizeLine) {
            sizeLine *= 2;
            char* tmp = realloc(line, sizeLine * sizeof(char));
            if (tmp) {
                line = tmp;
            } else {
                free(line);
                exit(0);
            }
        }

        line[lastChar++] = currChar;

        currChar = getchar();
        if (currChar == -1) {
            callError(lineNo);
            free(line);
            return false;
        }
    }

    line[lastChar] = '\0';
    bool result = executeLine(map, lineNo ,lastChar, line);
    free(line);
    return result;
}