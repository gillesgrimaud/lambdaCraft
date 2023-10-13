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

