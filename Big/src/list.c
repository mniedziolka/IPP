/** @file
 * Implementacja list.h.
 *
 * @author Michał Niedziółka <michal.niedziolka@students.mimuw.edu.pl>
 * @copyright Michał Niedziółka
 * @date 10.05.2019
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "list.h"

List* newList(void) {
    List* list = malloc(sizeof(List));

    if (list) {
        list->data = NULL;
        list->next = NULL;
    }

    return list;
}


List* listPushFront(List** head, void *new_data) {
        List* new_node = (List*)malloc(sizeof(List));

        if (new_node) {
            new_node->next = (*head);
            new_node->data = new_data;
            (*head) = new_node;
        }

        return new_node;
}


List* getLast(List* node) {
    while (node->next->next) {
        node = node->next;
    }

    return node;
}


void popLast(List* head) {
    while (head->next->next) {
        head = head->next;
    }

    freeList(head->next);
    head->data = NULL;
    head->next = NULL;
}


List* copyList(List* head) {
    List* newHead = newList();
    newHead->data = head->data;
    newHead->next = newList();
    List* node = newHead->next;
    head = head->next;

    while (head->next) {
        node->data = head->data;
        node->next = newList();

        head = head->next;
        node = node->next;
    }

    return newHead;
}


void freeList(List *root) {
    List *node = root;
    while (node->next) {
        List *tmp = node;
        node = node->next;
        tmp->data = NULL;
        tmp->next = NULL;
        free(tmp);
    }
    free(node);
}
