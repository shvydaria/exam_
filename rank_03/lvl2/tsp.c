// Header
#ifndef TSP_H
# define TSP_H
# include <stdio.h>
# include <math.h>

float calc_dist(float x1, float y1, float x2, float y2);
void  solve(int current_city, int count, float current_dist);

#endif
// Header 

float x[15];
float y[15];
int n = 0;
int visited[15];
float min_dist = 1000000000.0;

float calc_dist(float x1, float y1, float x2, float y2) {
	float x_diff = x1 - x2;
	float y_diff = y1 - y2;
	return (sqrtf((x_diff * x_diff) + (y_diff * y_diff)));
}

void solve(int current_city, int count, float current_dist) {
	int i;

	if(count == n) {
		float drive_home = calc_dist(x[current_city], 
			y[current_city], x[0], y[0]);
		float total_trip = current_dist + drive_home;
		if (total_trip < min_dist) {
			min_dist = total_trip;
		}
		return;
	}
	
	i = 0;
	while(i < n) {
		if(visited[i] == 0) {
			visited[i] = 1; // Place (Lock)
			solve(i, count + 1, current_dist + calc_dist(x[current_city], 
				y[current_city], x[i], y[i])); // Recurse
			visited[i] = 0; // Undo (Backtrack)
		}
		i++;
	}
}

int main (void) {
	while (fscanf(stdin, "%f, %f", &x[n], &y[n]) == 2) 
		n++;
		
	if (n == 0) // Edge case: if the file is empty!
		return (0);

	visited[0] = 1;
	solve(0, 1, 0.0);
	printf("%.2f\n", min_dist);
	return (0);
}