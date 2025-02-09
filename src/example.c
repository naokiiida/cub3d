/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:51:11 by niida             #+#    #+#             */
/*   Updated: 2025/02/09 15:23:00 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void calculateStepAndSideDist(t_vector2d rayDir, t_position mapPos, t_vector2d pos, t_vector2d *sideDist, t_vector2d *deltaDist, t_position *step) {
    if(rayDir.x < 0) {
        step->x = -1;
        sideDist->x = (pos.x - mapPos.x) * deltaDist->x;
    } else {
        step->x = 1;
        sideDist->x = (mapPos.x + 1.0 - pos.x) * deltaDist->x;
    }
    if(rayDir.y < 0) {
        step->y = -1;
        sideDist->y = (pos.y - mapPos.y) * deltaDist->y;
    } else {
        step->y = 1;
        sideDist->y = (mapPos.y + 1.0 - pos.y) * deltaDist->y;
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
        if (mapPos->x >= 0 && mapPos->x < MAP_WIDTH && mapPos->y >= 0 && mapPos->y < MAP_HEIGHT && worldMap[mapPos->y][mapPos->x] != 0) {
            *hit = 1;
        }
    }
}

int main() {
    t_vector2d pos = {5.0, 5.0}; // Player position
    t_vector2d dir = {-1.0, 1.0}; // Initial direction vector
    t_vector2d plane = {0.0, 0.66}; // Camera plane

    int x = 0;
    while (x < SCREEN_WIDTH) {
        double cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1; // screen range -1 to 1
        t_vector2d rayDir = calculateRayDir(dir, plane, cameraX);
        t_position mapPos = {(int)pos.x, (int)pos.y};
        t_vector2d sideDist;
        t_vector2d deltaDist = {fabs(1 / rayDir.x), fabs(1 / rayDir.y)};
        t_position step;
        int hit = 0;
        int side;

        calculateStepAndSideDist(rayDir, mapPos, pos, &sideDist, &deltaDist, &step);
        performDDA(&mapPos, &sideDist, deltaDist, step, &hit, &side);

        double perpWallDist;
        if(side == 0)
            perpWallDist = (sideDist.x - deltaDist.x);
        else
            perpWallDist = (sideDist.y - deltaDist.y);

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
    return 0;
}
