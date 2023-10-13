# LambdaCraft

LambdaCraft is a project aiming to bring the power of lambda functions and functional 
constructs such as fold and map to C. With LambdaCraft, you can write concise and expressive 
code for operations on arrays and linked structures.

## Features

- **Lambda functions**: Define anonymous functions on-the-fly.
- **Fold**: Reduce an array or structure to a single value.
- **Map**: Transform each element in an array or structure.

## Usage

Copy/Include the `lambda.h` header file in your project.

```c
#include "lambda.h"
```

## Examples

Examples demonstrating the power and usage of the provided constructs can be found in:

- `fold_array_example.c`
- `fold_struct_example.c`
- `map_array_example.c`
- `map_struct_example.c`

## Compilation

Use the provided Makefile to compile the examples:

``make all``

The project REQUIRES the GCC compiler (tested with version 13.2.0) using the gnu99 standard; Clang is not supported.

## Understanding Lambda Functions in C with LambdaCraft

In the realm of programming, the concept of lambda functions is most often associated with 
functional languages. However, the ability to use anonymous functions in C, a decidedly 
imperative language, opens up a myriad of possibilities. The LambdaCraft library provides 
this very capability. Before diving into using lambda functions in C, it's crucial to 
understand some of their unique characteristics and potential pitfalls.

### Scope of Lambda Functions

Lambda functions can only be associated with:

1. Local variables;
2. Structures of local variables;
3. Parameters of functions.

This scope restriction ensures consistent behavior, especially regarding memory management 
and the call stack.

### Return Constraints

Lambda functions cannot be returned by a function. Why? The reason is tied to the underlying 
mechanism by which these lambda functions work. When you declare a lambda function, it 
essentially translates to a local variable's address. If you try to return this address, 
you'll run into stack inconsistency issues, much like when you attempt to return the address 
of a local variable from a function. Doing so would lead to unpredictable behavior, as the 
local variable (or lambda function) would no longer exist after the function exits.

## Nested Variables

Nested variables refer to variables captured from an outer scope by the lambda function. 
For instance, if you have a lambda function inside a function, and this lambda function 
uses variables declared in its containing function, these variables are referred to as 
"nested variables."

LambdaCraft allows for multiple levels of nested variable usage. That is, you can have 
lambda functions inside lambda functions, each having access to the outer function's variables.

### Lambda Functions in Data Structures

While lambda functions can be manipulated in data structures just like any other function 
pointers, there's a crucial distinction: these pointers encapsulate the nested variables. 
This encapsulation means that any change to the nested variables reflects across all 
instances where the lambda function is used.

It's crucial to use this feature with caution. Nested variables maintain their state, 
and manipulating them can lead to unexpected results if not handled judiciously.

## Deep Dive into Nested Functions in GNU99 and its Implications

Nested functions, a feature available in GNU C (specifically GNU99), are not part of the 
standard C specification. But when used, they offer powerful capabilities, especially when 
writing more functional-style code in C. However, there are certain runtime implications 
when using nested functions. In this section, we'll dive deep into how these work under 
the hood and what it means for your code's performance and security.

### 1. Frame Chaining

When using nested functions, GCC employs a mechanism called frame chaining. Essentially, 
when a nested function needs to access the variables from its enclosing function, it uses a 
chain of pointers to reference these frames (or scopes). On architectures like Intel-compatible 
processors, the `r10` register, as standardized by the EABI, is used to manage this frame 
pointer chain.

### 2. Trampoline Functions on the Stack

A trampoline function is a small piece of code written directly onto the stack to help in 
invoking a nested function. The trampoline sets up the environment correctly, ensuring the 
nested function has access to the enclosing function's local variables. This is how nested 
functions are able to 'remember' the context of their enclosing function, even after it has 
exited.

### 3. Executable Stack Implications

Because of the trampoline mechanism, the stack needs to be executable. This diverges from the 
typical security best practice of having a non-executable stack to mitigate certain types of 
attacks, notably stack-based buffer overflows. When compiling code with nested functions, it's 
vital to be aware that the -z execstack option is implicitly set, making the stack executable. 
This could have security implications if not managed carefully.

### 4. Performance Overheads

While the power of nested functions and the ability to use lambdas in C is undeniable, there 
are performance costs:

**Trampoline Execution**: The very nature of writing and executing trampoline functions 
introduces an overhead. For performance-critical sections, this can be a factor.

**Deeply Nested Variables**: When nested functions are embedded within one another at multiple 
levels, traversing the frame pointer chain to access nested variables can introduce latency. 
The deeper the nesting, the more pronounced this overhead becomes.

## License

This project is licensed under the LGPLv3. Please see the header of the source files for 
detailed information

