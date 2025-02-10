/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:51:11 by niida             #+#    #+#             */
/*   Updated: 2025/02/10 12:20:00 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100

typedef struct vector2d
{
	double	x;
	double	y;
}	t_vector2d;

typedef struct position
{
	int	x;
	int	y;
}	t_position;

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

t_vector2d calculateRayDir(t_vector2d dir, t_vector2d plane, double cameraX) {
	t_vector2d rayDir;
	rayDir.x = dir.x + plane.x * cameraX;
	rayDir.y = dir.y + plane.y * cameraX;
	return rayDir;
}


/**
	* Calculates the distance to the next side (integer unit) in the grid for each direction.
	* This function computes the delta distance for the ray in both x and y directions.
	* The delta distance is the distance the ray has to travel to move from one x-side to the next x-side,
	* or from one y-side to the next y-side.
	*
	* @param rayDir The direction vector of the ray.
	* @return A vector containing the delta distances in x and y directions.
	*/
t_vector2d calculateDeltaDist(t_vector2d rayDir)
{
	t_vector2d deltaDist;
	deltaDist.x = fabs(1 / rayDir.x);
	deltaDist.y = fabs(1 / rayDir.y);

	//unoptimized:
	// vRayUnitStepSize.x = sqrt(1 + (vRayDir.y / vRayDir.x) * (vRayDir.y / vRayDir.x));
	// vRayUnitStepSize.y = sqrt(1 + (vRayDir.x / vRayDir.y) * (vRayDir.x / vRayDir.y));
	return deltaDist;
}

double calculateCameraX(int x) {
	double cameraX;

	cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1;
	assert(cameraX >= -1.0 && cameraX <= 1.0);
	return cameraX;
}

void calculateStepAndSideDist(t_vector2d rayDir, t_position mapPos, t_vector2d pos, t_vector2d *sideDist, t_vector2d deltaDist, t_position *step) {
	if(rayDir.x < 0) {
		step->x = -1;
		sideDist->x = (pos.x - mapPos.x) * deltaDist.x;
	} else {
		step->x = 1;
		sideDist->x = (mapPos.x + 1.0 - pos.x) * deltaDist.x;
	}
	if(rayDir.y < 0) {
		step->y = -1;
		sideDist->y = (pos.y - mapPos.y) * deltaDist.y;
	} else {
		step->y = 1;
		sideDist->y = (mapPos.y + 1.0 - pos.y) * deltaDist.y;
	}
}

void performDDA(t_position *mapPos, t_vector2d *sideDist, t_vector2d deltaDist, t_position step, int *hit, int *side) {
	while (*hit == 0) {
		if (sideDist->x < sideDist->y) {
			sideDist->x += deltaDist.x;
			mapPos->x += step.x;
			*side = 0;
		} else {
			sideDist->y += deltaDist.y;
			mapPos->y += step.y;
			*side = 1;
		}
		if (mapPos->x >= 0 && mapPos->x < MAP_WIDTH
			&& mapPos->y >= 0 && mapPos->y < MAP_HEIGHT && worldMap[mapPos->y][mapPos->x] != 0) {
			*hit = 1;
		}
	}
}

double calculatePerpWallDist(int side, t_vector2d sideDist, t_vector2d deltaDist) {
	if(side == 0)
		return (sideDist.x - deltaDist.x);
	else
		return (sideDist.y - deltaDist.y);
}

void renderFrame(t_vector2d pos, t_vector2d dir, t_vector2d plane) {
	int x = 0;
	while (x < SCREEN_WIDTH) {
		double cameraX = calculateCameraX(x);
		t_vector2d rayDir = calculateRayDir(dir, plane, cameraX);
		t_position mapPos = {(int)pos.x, (int)pos.y};
		t_vector2d deltaDist = calculateDeltaDist(rayDir);
		t_vector2d sideDist;
		t_position step;
		int hit = 0;
		int side;

		calculateStepAndSideDist(rayDir, mapPos, pos, &sideDist, deltaDist, &step);
		performDDA(&mapPos, &sideDist, deltaDist, step, &hit, &side);

		double perpWallDist = calculatePerpWallDist(side, sideDist, deltaDist);

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		// Output a very basic representation of the wall by printing '#' for the wall
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			if(y >= drawStart && y < drawEnd)
				printf("#");
			else
				printf("_");
		}
		printf("\n");
		x++;
	}
}

void testCalculateRayDir() {
	t_vector2d dir = {-1.0, 1.0};
	t_vector2d plane = {0.0, 0.66};
	double cameraX = 0.0;
	t_vector2d rayDir = calculateRayDir(dir, plane, cameraX);
	assert(fabs(rayDir.x - (-1.0)) < 1e-6);
	assert(fabs(rayDir.y - 1.0) < 1e-6);
}

void testCalculateStepAndSideDist() {
	t_vector2d rayDir = {-1.0, 1.0};
	t_position mapPos = {5, 5};
	t_vector2d pos = {5.1, 5.4};
	t_vector2d sideDist;
	t_vector2d deltaDist = calculateDeltaDist(rayDir);
	t_position step;
	calculateStepAndSideDist(rayDir, mapPos, pos, &sideDist, deltaDist, &step);
	printf("sideDist:(%f,%f)\n",sideDist.x, sideDist.y);
	assert(step.x == -1);
	assert(step.y == 1);
	assert(fabs(sideDist.x - deltaDist.x) < 1e-6);
	assert(fabs(sideDist.y - deltaDist.y) < 1e-6);
}


void testPerformDDA() {
	t_vector2d rayDir = {1.0, 0.0}; // Ray moving to the right
	t_position mapPos = {1, 1}; // Starting position
	t_vector2d pos = {1.5, 1.5}; // Player position
	t_vector2d deltaDist = calculateDeltaDist(rayDir);
	t_vector2d sideDist;
	t_position step;
	int hit = 0;
	int side;

	calculateStepAndSideDist(rayDir, mapPos, pos, &sideDist, deltaDist, &step);
	performDDA(&mapPos, &sideDist, deltaDist, step, &hit, &side);

	assert(hit == 1);
	printf("mapPos:(%d,%d)\n",mapPos.x, mapPos.y);
	assert(mapPos.x == 2); // The ray should hit the wall at x = 2
	assert(mapPos.y == 1); // The ray should stay at y = 1
}

void testCalculatePerpWallDist() {
	t_vector2d sideDist = {1.0, 2.0};
	t_vector2d deltaDist = {1.0, 1.0};
	int side = 0;
	double perpWallDist = calculatePerpWallDist(side, sideDist, deltaDist);
	assert(fabs(perpWallDist - 0.0) < 1e-6);
	side = 1;
	perpWallDist = calculatePerpWallDist(side, sideDist, deltaDist);
	assert(fabs(perpWallDist - 1.0) < 1e-6);
}

int main() {
	// Run tests
	testCalculateRayDir();
	// testCalculateStepAndSideDist();
	testPerformDDA();
	testCalculatePerpWallDist();

	// Render frame
	t_vector2d pos = {5.0, 5.0}; // Player position
	t_vector2d dir = {-1.0, 1.0}; // Initial direction vector
	t_vector2d plane = {0.0, 0.66}; // Camera plane
	renderFrame(pos, dir, plane);

	printf("All tests passed!\n");
	return 0;
}

void testVectorBounds(t_vector2d vector)
{
	assert(vector.x >= -1.0 && vector.x <= 1.0);
	assert(vector.y >= -1.0 && vector.y <= 1.0);
}
