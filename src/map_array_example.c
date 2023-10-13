/**
 * @file map_array_example.c
 * @brief Example of using the map function with an array in LambdaCraft.
 *
 * Copyright (C) 2023 [Votre nom ou le nom de votre organisation]
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
 * - Gilles Grimaud <[Votre email]>
 */

#include <stdio.h>
#include "lambda.h"

int main(int argc, char **argv) {
    // Nested value for the map operation
    double nestedValue = 0.5;

    // Source array of double values
    double sourceNumbers[9] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1};
    
    // Destination array to store the result
    double mappedNumbers[9];

    // Map operation on the array
    map(double, sourceNumbers, 9,
        {return value + nestedValue;},
        mappedNumbers
    );

    // Display the mapped results
    for(int i = 0; i < 9; i++) {
        printf("Source: %f -> Mapped: %f\n", sourceNumbers[i], mappedNumbers[i]);
    }

    return 0;
}

