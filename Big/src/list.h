/** @file
 * Interfejs listy
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 29.04.2019
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stdbool.h>
#include <stdlib.h>

/**
 * Struktura przechowująca generyczną listę.
 */
typedef struct List {
    void  *data; ///< wskaźnik na dane przechowywane w liście
    struct List *next; ///< wskaźnik na następny element listy
} List;

/** @brief Tworzy nową strukturę.
 * Tworzy nową, pustą listę, w której następny element równy jest @p NULL.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 * zaalokować pamięci.
 */
List* newList(void);

/** @brief Zwalnia strukturę.
 * Zwalnia całą listę. Nie zwalnia pamięci pod wskaźnikiem @p data.
 * @param[in,out] root – wskaźnik na początek listy;
 */
void freeList(List *root);

/** @brief Dokłada nowy element na początek.
 * Alokuje nowy węzeł listy, przepisuje dane, dokleja jako ogon starą listę.
 * @param[in,out] head      – początek listy do której będzie doklejany element;
 * @param[in,out] new_data  – nowe dane do dołączenia do listy;
 * @return Wartość @p true, jeśli udało się poprawnie dodać element.
 *         Wartość @p false, jeśli alokacja nie powiodła się.
 * zaalokować pamięci.
 */
List* listPushFront(List** head, void *new_data);

/** @brief Usuwa ostatni element z listy.
 * Zwalnia pamięć zarezerwowaną na ostatni element listy.
 * @param[in,out] head      – początek listy z końca której element
 *                            będzie usuwany;
 */
void popLast(List* head);

/** @brief Kopiuje listę.
 * Alokuje potrzebną pamięć i przepisuje listę.
 * @param[in,out] head      – początek listy z końca której element
 *                            będzie usuwany;
 */
List* copyList(List* head);

/** @brief Zwraca ostatni element listy.
 * Iteruje się po wszystkich elementach listy, po czym zwraca ostatni.
 * @param[in,out] node      – początek listy do której będzie doklejany element;
 * @return Wskaźnik na ostatni element.
 */
List* getLast(List* node);

#endif //__LIST_H__
