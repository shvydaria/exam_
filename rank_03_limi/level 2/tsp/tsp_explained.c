#include <stdio.h>      // For input/output functions like printf and scanf
#include <math.h>       // For mathematical functions like sqrtf

float x[11], y[11];     // Arrays to store the x and y coordinates of up to 11 points
int n, used[11];        // n: number of points; used[i]: flag to indicate if point i is visited
float min_dist = 1e9;   // Stores the minimum distance found, initialized to a large value

// Computes the Euclidean distance between point i and point j
float dist(int i, int j)
{
    // sqrtf computes the square root of the sum of squared differences in x and y
    return sqrtf((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

// Recursive function to solve the Traveling Salesman Problem (TSP)
// pos: current position (index of the current point)
// count: number of points visited so far
// cost: total distance traveled so far
void solve(int pos, int count, float cost)
{
    // Base case: if all points have been visited
    if (count == n)
    {
        // Add the distance to return to the starting point (index 0)
        cost += dist(pos, 0);
        // If this total cost is less than the current minimum, update min_dist
        if (cost < min_dist)
            min_dist = cost;
    }
    // Try visiting each unvisited point
    for (int i = 0; i < n; i++)
    {
        if (!used[i]) // If point i has not been visited yet
        {
            used[i] = 1; // Mark point i as visited
            // Recursively visit the next point, incrementing count and adding distance
            solve(i, count + 1, cost + dist(pos, i));
            used[i] = 0; // Backtrack: unmark point i for other permutations
        }
    }
}

int main(void)
{
    n = 0; // Initialize number of points to 0
    // Read up to 11 pairs of floats (x, y coordinates) from input
	// pay attention to what the subjct says on the exam the format we use scanf could be "%f %f" without a comma for example
    while (n < 11 && scanf("%f, %f", &x[n], &y[n]) == 2)
        n++;

    used[0] = 1; // Start from the first point (index 0), mark as visited
    solve(0, 1, 0); // Begin recursive search from point 0, with 1 point visited and 0 cost
    printf("%.2f\n", min_dist); // Output the minimum distance found, formatted to 2 decimals
    return 0; // Indicate successful program termination
}

/*
Test cases for TSP (input format: x, y per line):

// Minimal case: 1 point
0, 0

// Two points (should return double the distance between them)
0, 0
3, 4

// Three points in a triangle
0, 0
1, 0
0, 1

// Four points in a square
0, 0
0, 1
1, 1
1, 0

// Five points in a cross
0, 0
0, 2
2, 2
2, 0
1, 1

// All points at the same location (distance should be 0)
1, 1
1, 1
1, 1

// Negative coordinates
-1, -1
-2, -3
4, 5

// Max points (11), random
0,0
1,2
2,3
3,4
4,5
5,6
6,7
7,8
8,9
9,10
10,11

// Edge: points on a straight line
0,0
1,0
2,0
3,0
4,0

// Edge: points on a circle (approximate)
1,0
0,1
-1,0
0,-1

// Edge: large coordinates
10000,10000
-10000,-10000
5000,5000

// Edge: floating point precision
0.1,0.1
0.2,0.2
0.3,0.3

// Edge: only two points, same location
5,5
5,5

// Edge: input with extra whitespace
  1 , 2
3 ,4

// Edge: input with negative and positive mix
-5, 5
5, -5
0, 0

// Stress: 11 points, all at origin
0,0
0,0
0,0
0,0
0,0
0,0
0,0
0,0
0,0
0,0
0,0

// Invalid: no input (should handle gracefully)
(empty input)
*/
