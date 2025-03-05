/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:57:15 by niida             #+#    #+#             */
/*   Updated: 2025/03/05 15:58:26 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#define VISITED 9

static int	flood_recursive(int **map, int x, int y, t_vars *vars)
{
	if (x >= vars->map_size.x || y >= vars->map_size.y || x < 0 || y < 0
		|| map[y][x] == 1 || map[y][x] == VISITED)
		return (EXIT_SUCCESS);
	if (map[y][x] == 0)
		return (err("flood_recursive", "misplaced player or floor"));
	map[y][x] = VISITED;
	if (flood_recursive(map, x + 1, y, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x - 1, y, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x, y + 1, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (flood_recursive(map, x, y - 1, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
instead of infill, flood from the outside. flood from 2.
if we find a 1, visited cell, or outside map boundary - success
if we find a 0, - failure
if we find a 2,
- recurse neighbouring cells until a wall is found.
- if we find a 0 - failure.
Finally, check the whole border for lefover 2
*/
static int	floodfill(int **map, t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < vars->map_size.y)
	{
		x = 0;
		while (x < vars->map_size.x)
		{
			if (map[y][x] == 2)
			{
				if (flood_recursive(map, x, y, vars) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			if (map[y][x] == 0 && (x == 0 || y == 0
				|| x == vars->map_size.x - 1 || y == vars->map_size.y - 1))
				return (err("floodfill", "misplaced player or floor"));
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
	// printf("\n---------flooded result-----------\n");
	// print_map(map, vars->map_size);
	// printf("\nMap size: (%d,%d) Current x: %d, y: %d\n",
	// 	vars->map_size.x, vars->map_size.y, x, y);

static int	fill_map(char *map_data, int **map, t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map_size.y)
	{
		x = -1;
		while (*map_data && *map_data != '\n')
		{
			++x;
			if (*map_data == '0')
				map[y][x] = 0;
			else if (*map_data == '1')
				map[y][x] = 1;
			else if (*map_data == ' ')
				map[y][x] = 2;
			else
				map[y][x] = 0;
			map_data++;
		}
		map_data++;
		while (++x < vars->map_size.x)
			map[y][x] = 2;
	}
	return (EXIT_SUCCESS);
}

static int	init_map(int ***map, int rows, int cols)
{
	int	i;

	*map = malloc(sizeof(int *) * rows);
	if (!(*map))
		return (err("init_map", "malloc failed for map rows"));
	i = 0;
	while (i < rows)
	{
		(*map)[i] = malloc(sizeof(int) * cols);
		if (!(*map)[i])
		{
			while (i > 0)
				free((*map)[--i]);
			free(*map);
			return (err("init_map", "malloc failed for map columns"));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	setup_map(char *map_data, t_vars *vars)
{
	if (load_map(map_data, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(&vars->map, vars->map_size.y, vars->map_size.x)
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fill_map(map_data, vars->map, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (floodfill(vars->map, vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
