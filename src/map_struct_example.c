/**
 * @file map_array_example.c
 * @brief Example of using the map function with an array in LambdaCraft.
 *
 * Copyright (C) 2023 Gilles Grimaud
 *
 * This file is part of LambdaCraft.
 *
 * LambdaCraft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LambdaCraft is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LambdaCraft. If not, see <https://www.gnu.org/licenses/>.
 *
 * Contributors:
 * - Gilles Grimaud <gilles.grimaud.code@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include "lambda.h"

/**
 * @brief Node structure for a simple singly linked list.
 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main(int argc, char **argv) {
    // Create a sample linked list.
    Node* head = malloc(sizeof(Node));
    head->data = 1;
    head->next = malloc(sizeof(Node));
    head->next->data = 2;
    head->next->next = malloc(sizeof(Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    // Print the original linked list.
    printf("Original list:\n");
    for(Node* ptr = head; ptr != NULL; ptr = ptr->next) {
        printf("%d -> ", ptr->data);
    }
    printf("NULL\n");

    // Map using the `map_s` macro to square the data of each node.
    Node* new_head = map_s(Node*, head, 
        { return value->next; }, 
        { 
            Node *r_value = malloc(sizeof(Node));
            r_value->data = value->data * value->data;
            r_value->next = next; 
            return r_value; 
        }
    );

    // Print the mapped list.
    printf("\nMapped list (squared values):\n");
    for(Node* ptr = new_head; ptr != NULL; ptr = ptr->next) {
        printf("%d -> ", ptr->data);
    }
    printf("NULL\n");

    // Cleanup the original linked list.
    while(head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    // Cleanup the new mapped linked list.
    while(new_head) {
        Node* temp = new_head;
        new_head = new_head->next;
        free(temp);
    }

    return 0;
}

