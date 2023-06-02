#ifndef TRADUNGEON_DIAMOND_SQUARE_H
#define TRADUNGEON_DIAMOND_SQUARE_H

#include "Array2D.h"

namespace tradungeon
{

bool isPowerOfTwo(int value);

// Diamond step is a subprocedure for diamond-square algorithm.
// It gives a random value for element at pos
// using average value of four diagonal corners.
//
// Example)
// pos = {2, 2}
// patch_size = 4
//
// a---b
// -----
// --e--
// -----
// c---d
//
// e = (a + b + c + d) / 4 + random value
void diamondStep(Array2D<double>& map, const Point& pos, int patch_size, double rand_range);

// Square step is a subprocedure for diamond-square algorithm.
// It gives a random value for element at pos
// using average value of horizontal and vertical neighbors.
//
// Example)
// pos = {2, 2}
// patch_size = 4
//
// --a--
// -----
// b-e-c
// -----
// --d--
//
// e = (a + b + c + d) / 4 + random value
void squareStep(Array2D<double>& map, const Point& pos, int patch_size, double rand_range);

// Generates a random heightmap where # vertices = edge_length + 1.
// Four corners are initialized with initial_value.
// Each inner points are randomized with average value plus random value in range [-rand_range, +rand_range].
// The randomness decreases exponentially, multiplying rand_decay to rand_range after an interation.
Array2D<double> diamondSquare(int edge_length, double initial_value, double rand_range, double rand_decay);

} // namespace tradungeon

#endif
