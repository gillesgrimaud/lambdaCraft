/**
 * @file linked_list_fold_example.c
 * @brief Example demonstrating the use of fold_s function with linked lists in LambdaCraft.
 *
 * Copyright (C) 2023 [Your Name or Your Organization's Name]
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
#include <string.h>
#include "lambda.h"

// Define a linked list structure
typedef struct linked_struct_s {
  char *item;
  struct linked_struct_s *next;
} linked_s;

int main(int argc, char **argv) {
    // Construct a linked list from command line arguments using fold
    linked_s *ls = fold(linked_s *, char *, argv, argc, 
    { 
      linked_s *le = malloc(sizeof(linked_s));
      le->next = acc;
      le->item = value;
      return le;
    }, NULL);
    
    // Calculate the total length of all command line arguments using fold_s
    int total_length = fold_s(int, linked_s *, ls, 
      { return value->next; }, 
      { return acc + strlen(value->item); }, 0);
    printf("Total length: %d\n", total_length);

    // Free memory of each linked list node using foreach_s
    foreach_s(linked_s *, ls, { linked_s *r=value->next; free(value); return r; });

    return 0;
}

