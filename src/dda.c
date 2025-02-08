/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:50:10 by niida             #+#    #+#             */
/*   Updated: 2025/02/08 20:41:57 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

double	get_ray(t_fov fov, char **map, double ray_dir_x, double ray_dir_y, int map_width, int map_height)
{
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		map_x;
	int		map_y;

	hit = 0;
	map_x = (int)fov.x;
	map_y = (int)fov.y;
	// Calculate delta_dist_x and delta_dist_y
	if (ray_dir_x == 0)
		delta_dist_x = 1e30; // large number to represent "infinite" distance
	else
		delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30; // large number to represent "infinite" distance
	else
		delta_dist_y = fabs(1 / ray_dir_y);
	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (fov.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - fov.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (fov.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - fov.y) * delta_dist_y;
	}
	// Perform DDA
	while (hit == 0)
	{
		// Jump to the next map square, either in x-direction or y-direction
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		// Check if map_x and map_y are within bounds
		if (map_x < 0 || map_x >= map_width || map_y < 0 || map_y >= map_height)
		{
			// If out of bounds, return a large distance
			return 1e30;
		}
		if (map[map_y][map_x] == '1')
			hit = 1;
	}
	// Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if (side_dist_x < side_dist_y)
		perp_wall_dist = (map_x - fov.x + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - fov.y + (1 - step_y) / 2) / ray_dir_y;
	return (perp_wall_dist);
}

int	main(void)
{
	char	**map;
	t_fov	fov;
	double	ray_dir_x;
	double	ray_dir_y;
	double	distance;
	char *map_data[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000002000001",
		"1001000000000000000000001",
		"1111111110110000011100001",
		"1000000000110000011101111",
		"1111011111111101110000001",
		"1111011111111101110101001",
		"1100000011010101110000001",
		"1000200000000000110000001",
		"1000000000000000110101001",
		"1000000000000000110000001",
		"1111111111111111111111111"
	};
	int rows;
	int cols;

	rows = sizeof(map_data) / sizeof(map_data[0]);
	cols = strlen(map_data[0]);
	map = map_data;
	// Example FOV
	fov.x = 22.0;
	fov.y = 12.0;
	fov.radian = 0.0; // Player's direction in radians
	// Example ray direction
	ray_dir_x = -1.0;
	ray_dir_y = 0.0;
	// Calculate distance to wall
	distance = get_ray(fov, map, ray_dir_x, ray_dir_y, cols, rows);
	printf("Distance to wall: %f\n", distance);
	return (0);
}
