/**
 * @file lambda.h
 * @brief Provide lambda function-like macros using the GNU99 C standard.
 *
 * This header file provides a set of macros for creating lambda functions and
 * functional programming constructs, such as fold and map, for arrays and structures.
 *
 * Copyright (C) 2023 Gilles Grimaud
 *
 * This file is part of the LambdaCraft project.
 *
 * LambdaCraft is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LambdaCraft  is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LambdaCraft. If not, see <https://www.gnu.org/licenses/>.
 *
 * Contributors:
 * - Gilles.Grimaud <gilles.grimaud.code@gmail.com>
 */

#ifndef _lambda_h
#define _lambda_h

/**
 * @brief Define a lambda function using the GNU99 C standard.
 * 
 * This macro provides a concise and readable way to create 
 * inline functions (lambdas) in C.
 * The created lambda can be assigned to function pointers or 
 * used directly for immediate invocation.
 * 
 * @param ret   Return type of the lambda function.
 * @param args  Argument list for the lambda function enclosed 
 *              in parentheses.
 * @param body  Body of the lambda function enclosed in braces.
 * 
 * Body:
 *   The body should contain the logic or computations that the 
 *   lambda function performs.
 * 
 * Usage:
 * @code
 *   // Call a sort function with a comparaison operator :
 *   sort(t,size,𝛌(int, (int a, int b), { return a > b; }));
 *   
 * @endcode
 */
#define 𝛌(ret, args, body) ({ret _𝛌 args body; _𝛌;})
#define lambda 𝛌

/**
 * @brief Performs a fold (also known as reduce) operation on 
 * an array of a specified type.
 * 
 * This macro facilitates the fold operation, which accumulates 
 * results by iterating through each element of an array.
 * The lambda function provided in the body is responsible 
 * for computing and returning the next accumulator value.
 * 
 * @param acc_type      The type of the accumulator variable. 
 *                      Represents the type of value being accumulated.
 * @param element_type  The type of the elements in the array.
 * @param in_array      The input array on which the fold operation is to be performed.
 * @param size          The number of elements in the input array.
 * @param body          The lambda function body which processes each array element. 
 *                      It should accept an element of the array in the variable acc
 *                      and return the next accumulator value.
 * @param init_acc      The initial value of the accumulator.
 * 
 * Body:
 *   The lambda body should process the current element (referenced 
 *   by `value`) and the current accumulator (referenced by `acc`).
 * 
 * Usage:
 * @code
 *   int numbers[] = {1, 2, 3, 4, 5};
 *   
 *   // Use fold to compute the sum of numbers in the array.
 *   printf("Sum = %d\n", 
 *      fold(int, int, numbers, 5, { return acc + value; }, 0));
 *   
 * @endcode
 */
#define fold(acc_type, element_type, in_array, size, body, init_acc) ({ \
  acc_type acc = init_acc;                                  \
  for(int i=0;i<size;i++)                                   \
    acc=𝛌(acc_type,(element_type value), body)(in_array[i]);\
  ; acc; })

/**
 * @brief Performs a fold (also known as reduce) operation 
 * on structures of a specified type.
 * 
 * This macro facilitates the fold operation on data structures, 
 * typically linked lists or similar structures.
 * The lambda functions provided in `next` and `body` are 
 * responsible for traversing the structure and computing
 * the accumulator respectively.
 * 
 * @param acc_type      The type of the accumulator variable. 
 *                      Represents the type of value being accumulated.
 * @param element_type  The type of the elements in the structure.
 * @param first_e       The first element or starting point 
 *                      for the fold operation.
 * @param next          The lambda function body responsible for getting 
 *                      the next element in the structure. 
 *                      Should return the next element or NULL if there's 
 *                      none left.
 * @param body          The lambda function body which processes the current 
 *                      element. It should accept the 
 *                      current element and return the next accumulator value.
 * @param init_acc      The initial value of the accumulator.
 * 
 * Body:
 *   The lambda body should process the current element 
 *  (referenced by `value`) and the current accumulator (referenced by `acc`).
 * 
 * Usage:
 * @code
 *   typedef struct Node {
 *     int data;
 *     struct Node* next;
 *   } Node;
 *   
 *   // Assuming nodes form a linked list of integers.
 *   printf("Sum = %d\n", 
 *    fold_s(int, Node*, head, 
 *      { return value->next; }, 
 *      { return acc + value->data; }, 0));
 *   
 * @endcode
 */
#define fold_s(acc_type, element_type, first_e, next, body, init_acc) ({\
  acc_type acc = init_acc;                        \
  for(element_type value=first_e; value!=NULL;    \
      value=𝛌(element_type, (), next)())          \
      acc=𝛌(acc_type,(), body)();                 \
  ; acc; })

/**
 * @brief Iterate over each element of a linked structure.
 *
 * This macro provides a concise way to iterate over each 
 * element in a structure-based linked list or chain. 
 * It hides the loop mechanics and delegates the "next" 
 * element discovery to the provided lambda function within 
 * the body.
 *
 * @param element_type    The type of the elements within the 
 *                        linked structure.
 * @param first_e         The starting element (usually the 
 *                        head of the linked list or chain).
 * @param body            A lambda function that returns the 
 *                        next element in the chain.
 * 
 * Usage:
 * @code
 *   foreach_s(a_linked_s *, head, { workwith(value); return value->next; }) ;
 * @endcode
 */
#define foreach_s(element_type, first_e, body) ({ \
  for(element_type value=first_e; value!=NULL;    \
    value=𝛌(element_type, (), body)())            \
  ; })

/**
 * @brief Performs a map operation on arrays of a specified type.
 * 
 * This macro facilitates the mapping of each element in 
 * an input array to an output array using a provided lambda 
 * function. 
 * The lambda function (body) is responsible for transforming 
 * or processing each individual element from the input array.
 * 
 * @param type      The type of the elements in the array.
 * @param in_array  The input array on which the mapping 
 *                  operation will be performed.
 * @param size      The size or number of elements in the 
 *                  input array.
 * @param body      The lambda function body responsible 
 *                  for processing each element. 
 *                  It should accept the current element 
 *                  (referenced by `value`) and return the 
 *                  transformed or processed value.
 * @param out_array The output array where the transformed/processed 
 *                  elements will be stored.
 * 
 * Usage:
 * @code
 *   int arr[] = {1, 2, 3, 4, 5};
 *   int squared[5];
 *   
 *   // Maps each number to its square.
 *   map(int, arr, 5, { return value * value; }, squared);
 *   
 *   // Now, squared contains {1, 4, 9, 16, 25}
 * @endcode
 */
#define map(type, in_array, size, body, out_array) ({     \
  for(int i=0;i<size;i++) {                               \
    out_array[i]=𝛌(type,(type value), body)(in_array[i]); \
  }; })

/**
 * @brief Performs a map operation on a linked list of 
 * structures of a specified type.
 * 
 * This macro facilitates the mapping of elements within 
 * a structure using a provided lambda function. 
 * It traverses elements starting from the provided first 
 * element, and uses another lambda function (`findnext`) to 
 * retrieve the next element in the structure.
 * The mapping lambda function (`body`) is responsible for 
 * processing each individual element.
 * 
 * @param type        Type of the elements in the structure.
 * @param first_e     Initial element of the structure from 
 *                    where the mapping operation begins.
 * @param findnext    Lambda function to determine and retrieve 
 *                    the next element in the structure. 
 *                    Should return NULL or equivalent when 
 *                    there are no more elements to process.
 * @param body        Lambda function body responsible for 
 *                    processing each element from variable "value". 
 *                    It should accept the current element and 
 *                    return the processed value.
 * 
 * Usage:
 * @code
 *   typedef struct Node {
 *     int data;
 *     struct Node* next;
 *   } Node;
 *   
 *   // ... Assuming we have a linked list with nodes...
 *   
 *   // Map each node's data to its square.
 *   map_s(Node*, head, { return value->next; }, 
 *    {  
 *      Node *r_value = malloc(sizeof(Node));
 *      r_value->data = value->data * value->data;
 *      r_value->next = next; // next is NULL or the next r_value return 
 *      return r_value; 
 *    });
 *   
 *   // Now, each node's data in the linked list is squared.
 * @endcode
 */
#define map_s(type, first_e, findnext, body) ({         \
  type aux(type value) {                                \
    if(!value) return value;                            \
    else {                                              \
      type next = 𝛌(type, (type next), findnext)(value);\
      next = aux(next);                                 \
      return 𝛌(type, (), body)();                       \
    }                                                   \
  } ; aux(first_e) ;})

#endif
