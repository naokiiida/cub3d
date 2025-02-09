/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:51:11 by niida             #+#    #+#             */
/*   Updated: 2025/02/09 13:11:10 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 100

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


int main() {
    double posX = 5.0, posY = 5.0; // Player position
    double dirX = -1.0, dirY = 1.0; // Initial direction vector
    double planeX = 0.0, planeY = 0.66; // Camera plane

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double cameraX = 2.0 * x / (double)SCREEN_WIDTH - 1; // screen range -1 to 1
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX, sideDistY;
        double deltaDistX = fabs(1/rayDirX);
        double deltaDistY = fabs(1/rayDirY);

        int stepX, stepY;
        int hit = 0;
        int side;

        if(rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if(rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT && worldMap[mapY][mapX] != 0) {
                hit = 1;
            }
        }

        double perpWallDist;
        if(side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

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
    }
    return 0;
}
