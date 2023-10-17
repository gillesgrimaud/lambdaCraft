/**
 * @file fold_array_example.c
 * @brief Example of using the fold function with an array in LambdaCraft.
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
#include "lambda.h"

int main(int argc, char **argv) {
    // Nested value for the fold operation
    double nestedValue = 0.01;

    // Array of double values
    double numbers[9] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1};

    // Fold operation on the array
    double result = fold(
        double, double, numbers, 9,
        {return acc + value + nestedValue;},
        0.0
    );

    // Display the result
    printf("%f\n", result);

    return 0;
}

